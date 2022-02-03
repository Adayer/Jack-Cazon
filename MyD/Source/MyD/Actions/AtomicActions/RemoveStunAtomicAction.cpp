// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoveStunAtomicAction.h"

void URemoveStunAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->RemoveStun();
	UE_LOG(LogTemp, Warning, TEXT("Removed character stun"));
}