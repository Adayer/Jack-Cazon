// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAtomicAction.h"

void UMoveAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {

	myGridManager->PutCharacterInCell(actionRecieverCharacter, distinyCell);

	UE_LOG(LogTemp, Warning, TEXT("Moved to a cell"));
}