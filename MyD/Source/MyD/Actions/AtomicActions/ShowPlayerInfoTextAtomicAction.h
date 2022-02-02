// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "ShowPlayerInfoTextAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UShowPlayerInfoTextAtomicAction : public UAtomicAction
{
	GENERATED_BODY()

public: FText textToShow;
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
