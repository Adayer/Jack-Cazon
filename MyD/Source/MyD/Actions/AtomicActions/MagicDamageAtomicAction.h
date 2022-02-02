// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "MagicDamageAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UMagicDamageAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: int reciebedDamage;
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
