// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAction.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "AtomicActions/MoveAtomicAction.h"
#include "../Cells/GridManager.h"

bool UMoveAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	UE_LOG(LogTemp, Warning, TEXT("Starting comprobations of Move Action"));

	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Destiny cell occuped"));
		return false;
	}

	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetMovementRange()) {
		UE_LOG(LogTemp, Warning, TEXT("Cell out of moving range"));
		return false;
	}

	return true;
}

void UMoveAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridManager::StaticClass(), FoundActors);

	if (FoundActors.Num() != 0) {
		AGridManager* gridManager = Cast<AGridManager>(FoundActors[0]);
		TArray<AHexCell*> path = *gridManager->GetAStarPath(actionLauncherCharacter->GetMyCell(), actionRecieverCell, actionLauncherCharacter->GetMovementRange());

		float elapsedTime = 0;
		for (int i = 0; i < path.Num(); ++i) {
			AHexCell* pathCell = path[path.Num() - i - 1];

			elapsedTime += TIME_BETWEEN_CELL_CHANGE;

			UMoveAtomicAction* moveAction = NewObject<UMoveAtomicAction>();
			moveAction->myGridManager = gridManager;
			moveAction->distinyCell = pathCell;
			actionLauncherCharacter->AddTickAction(moveAction, elapsedTime);
		}

		UE_LOG(LogTemp, Warning, TEXT("Move action executed"));
	}
	
}