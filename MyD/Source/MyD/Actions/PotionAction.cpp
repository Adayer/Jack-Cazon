// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"

void UPotionAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionLauncherCharacter->RecieveHealing(actionLauncherCharacter->GetHP() / 2);
	UE_LOG(LogTemp, Warning, TEXT("Potion action"));
}