// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"

bool UAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	FVector actionLauncherCharacterPosition = actionLauncherCharacter->GetActorLocation();
	//FVector actionRecieverCharacterPosition = actionRecieverCell->GetActorLocation();
	FVector actionRecieverCharacterPosition = FVector();

	if (FVector::Dist2D(actionLauncherCharacterPosition, actionRecieverCharacterPosition) < actionLauncherCharacter->GetAttackRange()) {
		return true;
	}

	return false;
}

void UAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	//actionRecieverCell->RecieveDamage(actionLauncherCharacter->GetAttackPower());
}