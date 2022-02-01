// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.generated.h"

class ACharacterActor;

/**
 * 
 */
UCLASS()
class MYD_API UAtomicAction : public UObject
{
	GENERATED_BODY()
	
public: UFUNCTION() virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
