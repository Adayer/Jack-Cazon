// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"

bool UAttackAction::CanExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {
	FVector actionLauncherCharacterPosition = actionLauncherCharacter->GetActorLocation();
	FVector actionRecieverCharacterPosition = actionRecieverCharacter->GetActorLocation();

	if (FVector::Dist2D(actionLauncherCharacterPosition, actionRecieverCharacterPosition) < actionLauncherCharacter->GetAttackRange()) {
		return true;
	}

	return false;
}

void UAttackAction::ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {

	actionRecieverCharacter->RecieveDamage(actionLauncherCharacter->GetAttackPower());	
}