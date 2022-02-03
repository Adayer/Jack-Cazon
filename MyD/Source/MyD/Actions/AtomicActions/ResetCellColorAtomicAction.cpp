// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetCellColorAtomicAction.h"

void UResetCellColorAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	paintedCell->ResetMaterial();
	UE_LOG(LogTemp, Warning, TEXT("Cell color reseted"));
}