// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockAction.h"
#include "PotionAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UPotionAction : public UBlockAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) override;
};
