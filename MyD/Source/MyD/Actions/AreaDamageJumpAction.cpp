// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaDamageJumpAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include <MyD/Cells/GridManager.h>
#include <MyD/Actions/AtomicActions/MoveAtomicAction.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UAreaDamageJumpAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridManager::StaticClass(), FoundActors);

	if (FoundActors.Num() != 0) {

		Super::ExecuteAction(actionLauncherCharacter, actionRecieverCell);

		AGridManager* gridManager = Cast<AGridManager>(FoundActors[0]);

		UMoveAtomicAction* moveAction = NewObject<UMoveAtomicAction>();
		moveAction->myGridManager = gridManager;
		moveAction->distinyCell = actionRecieverCell;
		actionLauncherCharacter->AddTickAction(moveAction, 0.f);
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Area jump action realized"));
}

bool UAreaDamageJumpAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{

	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return false;
	}

	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetMovementRange()) {
		return false;
	}

	return true;
}
