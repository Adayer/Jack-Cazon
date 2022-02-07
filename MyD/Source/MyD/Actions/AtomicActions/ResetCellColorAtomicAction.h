// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "ResetCellColorAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UResetCellColorAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: AHexCell* paintedCell;

public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
