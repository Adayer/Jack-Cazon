// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "RemoveStunAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API URemoveStunAtomicAction : public UAtomicAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
