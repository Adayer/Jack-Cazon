// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

bool UAction::PerformAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	if (actionLauncherCharacter != nullptr && actionRecieverCell != nullptr && CanExecuteAction(actionLauncherCharacter, actionRecieverCell)) {
		ExecuteAction(actionLauncherCharacter, actionRecieverCell);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("The conditions for performing the action are not met"));
	return false;
}

bool UAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	return true;
}

void UAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	UE_LOG(LogTemp, Warning, TEXT("This is the base clase for making actions, override ExecuteAction & CanExecuteAction methods to create new action effects"));
}