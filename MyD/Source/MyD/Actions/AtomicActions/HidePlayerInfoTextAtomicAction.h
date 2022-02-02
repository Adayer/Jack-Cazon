// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicAction.h"
#include "HidePlayerInfoTextAtomicAction.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UHidePlayerInfoTextAtomicAction : public UAtomicAction
{
	GENERATED_BODY()
	
public: virtual void ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter);
};
