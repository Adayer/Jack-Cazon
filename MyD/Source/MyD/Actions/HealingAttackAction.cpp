// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingAttackAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"

void UHealingAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	int previousAttackedCharacterCurrentHP = actionRecieverCell->GetCharacterInCell()->GetCurrentHP();

	Super::ExecuteAction(actionLauncherCharacter, actionRecieverCell);

	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		actionLauncherCharacter->RecieveHealing(previousAttackedCharacterCurrentHP - actionRecieverCell->GetCharacterInCell()->GetCurrentHP());
	}
	else {
		actionLauncherCharacter->RecieveHealing(previousAttackedCharacterCurrentHP);
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Healing attack action realized"));
}