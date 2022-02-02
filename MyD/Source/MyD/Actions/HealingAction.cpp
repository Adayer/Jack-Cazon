// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingAction.h"
#include "../CharacterActor.h"
#include "../Cells/HexCell.h"


bool UHealingAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr && actionLauncherCharacter->GetTeam() == actionRecieverCell->GetCharacterInCell()->GetTeam()) {
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No ally in selected cell"));
	return false;
}

void UHealingAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	actionRecieverCell->GetCharacterInCell()->RecieveHealing(5);
	UE_LOG(LogTemp, Warning, TEXT("Healing action realized"));
}
