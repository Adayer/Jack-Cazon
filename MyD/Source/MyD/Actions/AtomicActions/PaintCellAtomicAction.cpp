// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintCellAtomicAction.h"

void UPaintCellAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	paintedCell->ChangeMaterial(valid);
	UE_LOG(LogTemp, Warning, TEXT("Cell painted"));
}