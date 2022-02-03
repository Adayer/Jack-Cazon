// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "CriticalAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UCriticalAttackAction : public UAction
{
	GENERATED_BODY()
	
public: virtual bool CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;
public: virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;

public: virtual bool IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;
};
