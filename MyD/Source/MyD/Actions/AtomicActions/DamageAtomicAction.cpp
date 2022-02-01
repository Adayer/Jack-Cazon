// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAtomicAction.h"

#include "../../CharacterActor.h"

void UDamageAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->RecieveDirectDamage(2);
	UE_LOG(LogTemp, Warning, TEXT("Direct damage applied"));
}