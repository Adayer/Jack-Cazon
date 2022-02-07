// Fill out your copyright notice in the Description page of Project Settings.


#include "TripleAttackAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include <MyD/Actions/AtomicActions/PhysicDamageAtomicAction.h>
#include <MyD/Actions/AtomicActions/PaintCellAtomicAction.h>
#include <MyD/Actions/AtomicActions/ResetCellColorAtomicAction.h>

bool UTripleAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No character in cell selected"));
		return false;
	}
	else if (actionRecieverCell->GetCharacterInCell()->GetTeam() == actionLauncherCharacter->GetTeam()) {
		UE_LOG(LogTemp, Warning, TEXT("Character selected is a team mate :("));
		return false;
	}

	return true;
}

void UTripleAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	int damagePerAttack = actionLauncherCharacter->GetAttackPower() / 2;

	UPaintCellAtomicAction* paintCellColorAtomicAction = NewObject<UPaintCellAtomicAction>();
	paintCellColorAtomicAction->paintedCell = actionRecieverCell;
	paintCellColorAtomicAction->valid = true;
	actionLauncherCharacter->AddTickAction(paintCellColorAtomicAction, 0.f);

	float elapsedActionTime = 0.f;
	for (int i = 0; i < 3; ++i) {
		elapsedActionTime += 1.f;

		UPhysicDamageAtomicAction* physicDamageAtomicAction = NewObject<UPhysicDamageAtomicAction>();;
		physicDamageAtomicAction->recievedDamage = damagePerAttack;

		actionRecieverCell->GetCharacterInCell()->AddTickAction(physicDamageAtomicAction, elapsedActionTime);
	}

	UResetCellColorAtomicAction* resetCellColorAtomicAction = NewObject<UResetCellColorAtomicAction>();
	resetCellColorAtomicAction->paintedCell = actionRecieverCell;
	actionLauncherCharacter->AddTickAction(resetCellColorAtomicAction, elapsedActionTime + 0.2f);
	
	UE_LOG(LogTemp, Warning, TEXT("Triple attack action realized"));
}

bool UTripleAttackAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetAttackRange()) {
		UE_LOG(LogTemp, Warning, TEXT("attacked character out of attack range"));
		return false;
	}

	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return actionRecieverCell->GetCharacterInCell()->GetTeam() != actionLauncherCharacter->GetTeam();
	}

	return true;
}
