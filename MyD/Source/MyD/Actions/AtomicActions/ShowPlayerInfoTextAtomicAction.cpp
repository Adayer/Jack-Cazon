// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowPlayerInfoTextAtomicAction.h"

#include "../../CharacterActor.h"

void UShowPlayerInfoTextAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {

	actionRecieverCharacter->ShowInfoText(textToShow);

	UE_LOG(LogTemp, Warning, TEXT("Showed character info text"));
}