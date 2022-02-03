// Fill out your copyright notice in the Description page of Project Settings.


#include "HidePlayerInfoTextAtomicAction.h"

#include "../../CharacterActor.h"

void UHidePlayerInfoTextAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {

	actionRecieverCharacter->HideInfoText();

	UE_LOG(LogTemp, Warning, TEXT("Character info text hiden"));
}