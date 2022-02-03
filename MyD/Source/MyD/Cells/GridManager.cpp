// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "../TurnSystem/CombatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

#include "../CharacterActor.h"
#include "../SpawnPoint.h"


// Sets default values
AGridManager::AGridManager()
{
	const FString ARCHER_TEXTURE = "Texture2D'/Game/Images/RolesImages/IconRolArcher.IconRolArcher'";
	ConstructorHelpers::FObjectFinder<UTexture2D> ArcherTexture(*ARCHER_TEXTURE);
	ArcherTextureObject = ArcherTexture.Object;
	
	const FString TANK_TEXTURE = "Texture2D'/Game/Images/RolesImages/IconRoleTank.IconRoleTank'";
	ConstructorHelpers::FObjectFinder<UTexture2D> TankTexture(*TANK_TEXTURE);
	TankTextureObject = TankTexture.Object;
	
	const FString MAGUE_TEXTURE = "Texture2D'/Game/Images/RolesImages/IconRolMague.IconRolMague'";
	ConstructorHelpers::FObjectFinder<UTexture2D> MagueTexture(*MAGUE_TEXTURE);
	MagueTextureObject = MagueTexture.Object;
}




// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGridManager::SpawnCharacters()
{
	TArray<AActor*> AllSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(this, ASpawnPoint::StaticClass(), AllSpawnPoints);
	

	for (auto sp : AllSpawnPoints)
	{
		ASpawnPoint* spawnPoint = Cast<ASpawnPoint>(sp);

		ACharacterActor* newChar = GetWorld()->SpawnActor<ACharacterActor>(CharacterBPClass);

		newChar->SetCharacterCell(spawnPoint->cellOwner);
		if (spawnPoint->cellOwner != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("Neighbour num: %d"), spawnPoint->cellOwner->neighbours.Num());
		}		

		PutCharacterInCell(newChar, spawnPoint->cellOwner);

		bool team = spawnPoint->team;
		newChar->SetTeam(spawnPoint->team);
		if (newChar->GetTeam())
		{
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(newChar->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			MeshComponent->SetMaterial(0, aTeamMat);
		}
		else
		{
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(newChar->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			MeshComponent->SetMaterial(0, bTeamMat);
		}

		switch (newChar->GetRol())
		{
		case Rol::Archer:
			{
			
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(newChar->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			MeshComponent->SetStaticMesh(archerMesh);
			newChar->SetIconTexture(ArcherTextureObject);

				break;
			}
		case Rol::Melee:
			{
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(newChar->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			MeshComponent->SetStaticMesh(tankMesh);
			newChar->SetIconTexture(TankTextureObject);
				break;
			}
		case Rol::Mague:
			{
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(newChar->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			MeshComponent->SetStaticMesh(magueMesh);
			newChar->SetIconTexture(MagueTextureObject);
				break;
			}
		}

	}

}

//Metodo comprobar walkable
// Store reference (and check) of Cell parameter
// Change cells color
//Store posible path

void AGridManager::OnHoverCell(AHexCell* cell, TArray<AHexCell*> ignoreCells)
{
	if (cell != lastCell)
	{
		if(lastCell != NULL && ignoreCells.Contains(lastCell) == false)lastCell->ResetMaterial();

		ACombatGameMode* CombatGM = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		TArray<UTurnOrderData*>* turnData = CombatGM->GetTurnOrderDataList();
		ACharacterActor* playerChar = (*turnData)[CombatGM->GetTurnIndex()]->GetCharacter();

		cell->ChangeMaterial(AStar(playerChar->GetMyCell(), cell, 8));
		lastCell = cell;
	}
}


/// /////////////////////////////////////////////////////////////////////////

void AGridManager::MovePawn()
{
	if (controller)
	{
		controller->MoveCharacter(path);
	}
	
}
bool AGridManager::PutCharacterInCell(ACharacterActor* placedCharacter, AHexCell* targetCell)
{
	if (targetCell == nullptr || targetCell->GetCharacterInCell() != nullptr || placedCharacter == nullptr) {
		return false;
	}

	placedCharacter->GetMyCell()->SetCharacterInCell(nullptr);
	targetCell->SetCharacterInCell(placedCharacter);
	placedCharacter->SetCharacterCell(targetCell);
	placedCharacter->SetActorLocation(targetCell->GetActorLocation());

	return true;
}
/// /////////////////////////////////////////////////////////////////////////

float Heuristic(AHexCell* a, AHexCell* b)
{
	return (FMath::Abs(a->hexCoord.X - b->hexCoord.X) + FMath::Abs(a->hexCoord.Y - b->hexCoord.Y) + FMath::Abs(a->hexCoord.X + a->hexCoord.Y - b->hexCoord.X - b->hexCoord.Y)) / 2;
}

void ResetAStartCells(TArray<AHexCell*> toReset)
{
	for (auto cell : toReset)
	{
		cell->ResetAStartProperties();
	}
}

bool AGridManager::AStar(AHexCell* start, AHexCell* end, float maxSteps)
{
	path.Empty();

	if (Heuristic(start, end)< maxSteps && end->characterInCell == NULL)
	{
		AHexCell* currentCell = start;
		start->localGoal = 0;
		start->globalGoal = Heuristic(start, end);

		TArray<AHexCell*> toCheckList;
		TArray<AHexCell*> toReset;
		toCheckList.Add(start);
		toReset.Add(start);

		while (toCheckList.Num())
		{
			toCheckList.Sort([](AHexCell& a, AHexCell& b) {	return a.globalGoal > b.globalGoal; }); //Comprobar que esto esta bien

			while (toCheckList.Num() && toCheckList.Last()->visited)
			{
				toCheckList.Pop();
			}
			if (!toCheckList.Num()) break;

			currentCell = toCheckList.Last();
			currentCell->visited = true;

			// Check neighbour cells
			for (AHexCell* neighbour : currentCell->neighbours)
			{
				if (neighbour->characterInCell == NULL) //---------------------> CAMBIAR POR CHARACTER IN CELL
				{
					int potentialLocalGoal = currentCell->localGoal + neighbour->weight; //Suma el peso de la casilla al local del anterior

					if (potentialLocalGoal < neighbour->localGoal)
					{
						neighbour->parent = currentCell;
						neighbour->localGoal = potentialLocalGoal;

						neighbour->globalGoal = neighbour->localGoal + Heuristic(neighbour, end);

						toReset.AddUnique(neighbour);
					}

					//Comprueba que los "pasos" hasta la casilla comprobada sea menor que los pasos maximos
					if (!neighbour->visited && neighbour->localGoal <= maxSteps)
					{
						toCheckList.Add(neighbour);
					}
				}
			}
		}
		//Condicion de resuelto con exito
		if (end->visited)
		{
			AHexCell* current = end;
			while (current != start)
			{
				path.Add(current);
				current = current->parent;
			}

			ResetAStartCells(toReset);
			return true;
		}
		ResetAStartCells(toReset);
	}

	return false;
}

TArray<AHexCell*>* AGridManager::GetAStarPath(AHexCell* start, AHexCell* end, float maxSteps)
{
	AStar(start, end, maxSteps);
	return &path;
}


