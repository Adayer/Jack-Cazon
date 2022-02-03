// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicDamageAtomicAction.h"

void UPhysicDamageAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->RecieveDamage(recievedDamage);
	UE_LOG(LogTemp, Warning, TEXT("Physic damage applied"));
}