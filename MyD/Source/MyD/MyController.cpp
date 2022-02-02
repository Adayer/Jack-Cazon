// Fill out your copyright notice in the Description page of Project Settings.


#include "MyController.h"
#include "Cells/GridManager.h"
#include "CharacterActor.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

AMyController::AMyController()
{
	SetActorTickEnabled(true);
}

void AMyController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	TArray<AActor*> foundArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AGridManager::StaticClass(), foundArray);
	if (foundArray.Num())
	{
		Grid = Cast<AGridManager>(foundArray[0]);
	}
}

void AMyController::Tick(float DeltaTime)
{
	/*
	* if (Walking)
	{
		if (path.Num())
		{
			if (cooldown <= 0)
			{
				currentCell = path.Pop();
				GetPawn()->SetActorLocation(currentCell->GetActorLocation());
				cooldown = 0.5f;
			}
			else
			{
				cooldown -= DeltaTime;
			}
		}
		else
		{
			Grid->PutCharacterInCell(Cast<ACharacterActor>(GetPawn()), currentCell);
			Walking = false;
		}
	}
	else 
	{
		FHitResult hitResult;
		if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult))
		{
			AHexCell* cell = Cast<AHexCell>(hitResult.Actor);
			selectedCell = cell;
			if (cell)
			{
				Grid->OnHoverCell(cell);

				if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
				{
					Grid->MovePawn();
				}
			}
		}
	}
	*/
	
	FHitResult hitResult;
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult))
	{
		AHexCell* cell = Cast<AHexCell>(hitResult.Actor);
		if (cell)
		{
			TArray<AHexCell*> ignoreCells;
			ignoreCells.Add(selectedCell);
			Grid->OnHoverCell(cell, ignoreCells);
		}
	}
}

void AMyController::MoveCharacter(TArray<AHexCell*>& _path)
{
	path = _path; //esto esta hecho super cutre, aedmas unavez que guarda el puntero no tendria que volver a pasarselo pero no me apetece pensar
	if (currentCell)
	{
		currentCell->SetCharacterInCell(nullptr);
	}
	Walking = true;
}

void AMyController::ResetSelectedCell()
{
	if (selectedCell != nullptr) {
		selectedCell->ResetMaterial();
	}

	selectedCell = nullptr;
}

void AMyController::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	// This is initialized on startup, you can go straight to binding
	InputComponent->BindAction("CellSelect", IE_Released, this, &AMyController::OnLeftMouseButtonPressed);
}

void AMyController::OnLeftMouseButtonPressed() {

	ResetSelectedCell();

	FHitResult hitResult;
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult))
	{
		AHexCell* cell = Cast<AHexCell>(hitResult.Actor);
		if (cell != nullptr) {
			selectedCell = cell;
			selectedCell->ChangeMaterial(true);
		}
		
	}
}

AHexCell* AMyController::GetSelectedCell()
{
	return selectedCell;
}