// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAction.h"
#include "BurningAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UBurningAttackAction : public UAttackAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;
};
