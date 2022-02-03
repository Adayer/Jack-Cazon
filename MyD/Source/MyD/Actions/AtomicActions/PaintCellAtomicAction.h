// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "PaintCellAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UPaintCellAtomicAction : public UAtomicAction
{
	GENERATED_BODY()
	
public: AHexCell* paintedCell;
public: bool valid;

public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
