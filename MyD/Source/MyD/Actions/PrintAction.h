// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "PrintAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UPrintAction : public UAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter) override;
};
