// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "ReduceDamageAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UReduceDamageAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: int damageVariation = 0;

public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
