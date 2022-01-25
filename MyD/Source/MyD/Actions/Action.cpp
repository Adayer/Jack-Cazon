// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

bool UAction::PerformAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {

	if (CanExecuteAction(actionLauncherCharacter, actionRecieverCharacter)) {
		ExecuteAction(actionLauncherCharacter, actionRecieverCharacter);
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Attack out of range"));
	}

	return false;
}

bool UAction::CanExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {
	return true;
}

void UAction::ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {
	UE_LOG(LogTemp, Warning, TEXT("This is the base clase for making actions, override ExecuteAction & CanExecuteAction methods to create new action effects"));
}