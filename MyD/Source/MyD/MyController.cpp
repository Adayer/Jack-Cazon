// Fill out your copyright notice in the Description page of Project Settings.


#include "MyController.h"
#include "Cells/GridManager.h"
#include "CharacterActor.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <MyD/Actions/AtomicActions/ResetCellColorAtomicAction.h>
#include <MyD/Actions/AtomicActions/PaintCellAtomicAction.h>

AMyController::AMyController()
{
	SetActorTickEnabled(true);

	actionLauncher = CreateDefaultSubobject<AActionLauncherActor>("actionLauncher");

	affectedCells = TArray<AHexCell*>();
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

	ResetSelectedCells();

	if (preparingAction) {
		FHitResult hitResult;
		if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult))
		{
			AHexCell* cell = Cast<AHexCell>(hitResult.Actor);
			if (cell)
			{
				selectedCell = cell;
				actionLauncher->SetActionRecieverCell(cell);
				affectedCells = actionLauncher->GetActionAffectedCells();
				for (AHexCell* affectedCell : affectedCells) {
					if (actionLauncher->GetActionLauncherComponent()->GetMyAction()->IsActionInRangeOfExecution(actionLauncher->GetActionLauncherCharacter(), affectedCell)) {
						affectedCell->ChangeMaterial(true);
					}
					else {
						affectedCell->ChangeMaterial(false);
					}
					
				}
				
			}
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

void AMyController::ResetSelectedCells()
{
	for (AHexCell* affectedCell : affectedCells) {
		affectedCell->ResetMaterial();
	}

	affectedCells.Empty();
}

void AMyController::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	// This is initialized on startup, you can go straight to binding
	InputComponent->BindAction("CellSelect", IE_Released, this, &AMyController::OnLeftMouseButtonPressed);
}

void AMyController::OnLeftMouseButtonPressed() {

	ResetSelectedCells();

	preparingAction = !actionLauncher->ExecuteAction();

}

TArray<AHexCell*> AMyController::GetAffectedCells()
{
	return affectedCells;
}

AHexCell* AMyController::GetSelectedCell()
{
	return selectedCell;
}

void AMyController::PrepareAction(UAction* actionToExecute, ACharacterActor* actionLauncherCharacter)
{
	preparingAction = true;
	actionLauncher->SetActionLaunchersAction(actionToExecute);
	actionLauncher->SetActionLauncherCharacter(actionLauncherCharacter);
}
