// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../BoardCharacter.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UAction : public UObject
{
	GENERATED_BODY()

public: UFUNCTION() bool PerformAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter);
public: UFUNCTION() virtual bool CanExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter);
public: UFUNCTION() virtual void ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter);
};
