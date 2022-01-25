// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

void UAction::PerformAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {
	FVector actionLauncherCharacterPosition = actionLauncherCharacter->GetActorLocation();
	FVector actionRecieverCharacterPosition = actionRecieverCharacter->GetActorLocation();

	if (FVector::Dist2D(actionLauncherCharacterPosition, actionRecieverCharacterPosition) < actionLauncherCharacter->GetAttackRange()) {
		ExecuteAction(actionLauncherCharacter, actionRecieverCharacter);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Attack out of range"));
	}
}

void UAction::ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {
	UE_LOG(LogTemp, Warning, TEXT("This is the base clase for making actions, override ExecuteAction method to create new action effects"));
}