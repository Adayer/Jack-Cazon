// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicDamageAtomicAction.h"

#include "../../CharacterActor.h"

void UMagicDamageAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->RecieveMagicDamage(reciebedDamage);
	UE_LOG(LogTemp, Warning, TEXT("Magic damage applied"));
}