// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockAction.h"
#include "../CharacterActor.h"

bool UBlockAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	
	return true;
}

void UBlockAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionLauncherCharacter->Block();
	UE_LOG(LogTemp, Warning, TEXT("Block action"));
}

bool UBlockAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	return actionLauncherCharacter->GetMyCell() == actionRecieverCell;
}