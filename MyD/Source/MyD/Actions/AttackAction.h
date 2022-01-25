// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "AttackAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UAttackAction : public UAction
{
	GENERATED_BODY()
	
public: virtual bool CanExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) override;
public: virtual void ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) override;
};
