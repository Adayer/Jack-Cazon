// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingAction.h"

bool UHealingAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return true;
	}

	return false;
}

void UHealingAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	actionRecieverCell->GetCharacterInCell()->RecieveHealing(5);
}
