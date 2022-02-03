// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "PhysicDamageAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UPhysicDamageAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: int recievedDamage;
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
