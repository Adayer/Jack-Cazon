// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "../../Cells/GridManager.h"
#include "../../Cells/HexCell.h"
#include "MoveAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UMoveAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: AGridManager* myGridManager;
public: AHexCell* distinyCell;

public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
