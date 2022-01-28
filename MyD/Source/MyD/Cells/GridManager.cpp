// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "../TurnSystem/CombatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../CharacterActor.h"
// Sets default values
AGridManager::AGridManager()
{
	const FString ORC_TEXTURE = "Texture2D'/Game/Andres/Sprite/OrcIcon.OrcIcon'";
	ConstructorHelpers::FObjectFinder<UTexture2D> OrcTexture(*ORC_TEXTURE);
	OrcTextureObject = OrcTexture.Object;
	
	const FString HUMAN_TEXTURE = "Texture2D'/Game/Andres/Sprite/HumanIcon.HumanIcon'";
	ConstructorHelpers::FObjectFinder<UTexture2D> HumanTexture(*HUMAN_TEXTURE);
	HumanTextureObject = HumanTexture.Object;
}

void AGridManager::SpawnCells()
{
	gridArray.SetNumZeroed(gridWidth);
	for (int x = 0; x < gridWidth; x++)
	{
		gridArray[x].SetNumZeroed(gridHeight);

		for (int y = 0; y < gridHeight; y++)
		{
			int oddRow = y % 2;
			const float xPos = x * XOffset + OddOffset * oddRow;
			const float yPos = y * YOffset;

			AHexCell* newCell = GetWorld()->SpawnActor<AHexCell>(BaseCell, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);

			int q = x - (y - y % 2) / 2;
			newCell->hexCoord = FIntPoint(q, y);
			gridArray[x][y] = newCell;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//APawn* pawn = GetWorld()->SpawnActor<APawn>(testPawn, gridArray[0][0]->GetActorLocation(), FRotator::ZeroRotator);
	controller = Cast<AMyController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//////////////////////////////////////////////////////////////////////////////

	// Set neighbours
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			bool oddRow = y % 2==1;
			if (y>0)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x][y-1]);

				if (oddRow)
				{
					if (x < gridWidth - 1)
					gridArray[x][y]->neighbours.Add(gridArray[x+1][y-1]);
				}
				else
				{
					if (x > 0)
					gridArray[x][y]->neighbours.Add(gridArray[x-1][y-1]);
				}
			}

			if (y < gridHeight - 1)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x][y+1]);

				if (oddRow)
				{
					if(x < gridWidth - 1)
					gridArray[x][y]->neighbours.Add(gridArray[x+1][y+1]);
				}
				else
				{
					if(x > 0)
					gridArray[x][y]->neighbours.Add(gridArray[x-1][y+1]);
				}
			}

			if (x>0)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x-1][y]);
			}

			if (x < gridWidth - 1)
			{
				gridArray[x][y]->neighbours.Add(gridArray[x+1][y]);
			}
		}
	}

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnCells();
	SpawnCharacter();
}

void AGridManager::SpawnCharacter()
{
	unsigned int numChars = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->NUM_PLAYERS;
	for (unsigned int i = 0; i < numChars; ++i)
	{
		int32 randValueX;
		int32 randValueY;
		do
		{
			randValueX = FMath::RandRange(0, gridWidth - 1);
			randValueY = FMath::RandRange(0, gridHeight - 1);
		} while (gridArray[randValueX][randValueY]->GetCharacterInCell());

		const FVector SpawnLocation = gridArray[randValueX][randValueY]->GetActorLocation();
		ACharacterActor* newChar = GetWorld()->SpawnActor<ACharacterActor>(CharacterBPClass);
		newChar->myCell = gridArray[randValueX][randValueY];
		gridArray[randValueX][randValueY]->SetCharacterInCell(newChar);
		newChar->SetActorLocation(SpawnLocation);

		if (i % 2 == 0)
		{
			newChar->SetIconTexture(OrcTextureObject);//TextureFinder.Object;
		}
		else
		{
			newChar->SetIconTexture(HumanTextureObject);//TextureFinder.Object;
		}
	}
}

//Metodo comprobar walkable
// Store reference (and check) of Cell parameter
// Change cells color
//Store posible path

void AGridManager::OnHoverCell(AHexCell* cell)
{
	if (cell != lastCell)
	{
		if(lastCell != NULL)lastCell->ResetMaterial();
		//Calcular algoritmo

		//AHexCell* playerPos = Cast<ACharacterActor>(); // - - - - - - - - ->Setear variable en otra parte
		ACombatGameMode* CombatGM = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		TArray<UTurnOrderData*>* turnData = CombatGM->GetTurnOrderDataList();
		ACharacterActor* playerChar = (*turnData)[CombatGM->GetTurnIndex()]->GetCharacter();

		cell->ChangeMaterial(AStar(playerChar->myCell, cell, 8));
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
/// /////////////////////////////////////////////////////////////////////////

float Heuristic(AHexCell* a, AHexCell* b)
{
	return (FMath::Abs(a->hexCoord.X - b->hexCoord.X) + FMath::Abs(a->hexCoord.Y - b->hexCoord.Y) + FMath::Abs(a->hexCoord.X + a->hexCoord.Y - b->hexCoord.X - b->hexCoord.Y)) / 2;
}

bool AGridManager::AStar(AHexCell* start, AHexCell* end, float maxSteps)
{
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			gridArray[x][y]->ResetAStartProperties();
		}
	}


	AHexCell* currentCell = start;
	start->localGoal = 0;
	start->globalGoal = Heuristic(start, end);  

	TArray<AHexCell*> toCheckList;
	toCheckList.Add(start);

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
			if (neighbour->free)
			{
				int potentialLocalGoal= currentCell->localGoal + neighbour->weight; //Suma el peso de la casilla al local del anterior

				if (potentialLocalGoal<neighbour->localGoal)
				{
					neighbour->parent = currentCell;
					neighbour->localGoal = potentialLocalGoal;

					neighbour->globalGoal = neighbour->localGoal + Heuristic(neighbour, end);
				}

				//Comprueba que los "pasos" hasta la casilla comprobada sea menor que los pasos maximos
				if (!neighbour->visited && neighbour->localGoal <= maxSteps)
				{	toCheckList.Add(neighbour);	}
			}
		}
	}


	GEngine->AddOnScreenDebugMessage(
		-1,        // don't over wrire previous message, add a new one
		0.35f,   // Duration of message - limits distance messages scroll onto screen
		FColor::Cyan.WithAlpha(64),   // Color and transparancy!
		FString::Printf(TEXT("        %f"), end->localGoal)  // Our usual text message format
	);

	//Condicion de resuelto con exito
	path.Empty();
	if (end->visited)
	{	
		AHexCell* current = end;
		while (current!= start)
		{
			path.Add(current);
			current = current->parent;
		}
		return true; 
	}
	else { return false; }
}


