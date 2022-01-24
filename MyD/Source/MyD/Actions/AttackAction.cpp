// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"

void UAttackAction::ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) {

	actionRecieverCharacter->RecieveDamage(actionLauncherCharacter->GetAttackPower());	
}