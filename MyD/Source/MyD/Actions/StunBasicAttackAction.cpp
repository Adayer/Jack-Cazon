// Fill out your copyright notice in the Description page of Project Settings.


#include "StunBasicAttackAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include <MyD/Actions/AtomicActions/PhysicDamageAtomicAction.h>

bool UStunBasicAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
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

void UStunBasicAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionRecieverCell->GetCharacterInCell()->GetStunned(2);

	UPhysicDamageAtomicAction* physicDamageAtomicAction = NewObject<UPhysicDamageAtomicAction>();;
	physicDamageAtomicAction->recievedDamage = actionLauncherCharacter->GetAttackPower();

	actionRecieverCell->GetCharacterInCell()->AddTickAction(physicDamageAtomicAction, 1.f);

	UE_LOG(LogTemp, Warning, TEXT("Attack action realized"));
}

bool UStunBasicAttackAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
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