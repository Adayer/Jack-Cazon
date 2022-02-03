// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealingAction.h"
#include "AttackBuffAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UAttackBuffAction : public UHealingAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell);
};
