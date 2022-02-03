// Fill out your copyright notice in the Description page of Project Settings.


#include "ReduceDamageAtomicAction.h"

void UReduceDamageAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->Modifyattack(damageVariation);
}