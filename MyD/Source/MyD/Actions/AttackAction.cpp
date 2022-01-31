// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"

bool UAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	if (actionRecieverCell->GetCharacterInCell() == nullptr) {
		return false;
	}

	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetAttackRange()) {
		return false;
	}

	return true;
}

void UAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionRecieverCell->GetCharacterInCell()->RecieveDamage(actionLauncherCharacter->GetAttackPower());
}