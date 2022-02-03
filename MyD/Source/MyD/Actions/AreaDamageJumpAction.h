// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireExplosionAction.h"
#include "AreaDamageJumpAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UAreaDamageJumpAction : public UFireExplosionAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell);
public: virtual bool IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;
};
