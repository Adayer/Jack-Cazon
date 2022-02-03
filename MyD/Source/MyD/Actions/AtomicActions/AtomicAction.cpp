// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomicAction.h"

#include "../../CharacterActor.h"

void UAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	UE_LOG(LogTemp, Warning, TEXT("This is the base ATOMIC action, overwrite ExecuteAtomicAction method in child classes"));
}
