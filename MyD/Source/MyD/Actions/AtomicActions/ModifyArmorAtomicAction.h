// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "ModifyArmorAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UModifyArmorAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: int armorVariation;
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
