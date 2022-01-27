// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MYD_API UAction : public UObject
{
	GENERATED_BODY()

public: UFUNCTION() bool PerformAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell);
public: UFUNCTION() virtual bool CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell);
public: UFUNCTION() virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell);
};
