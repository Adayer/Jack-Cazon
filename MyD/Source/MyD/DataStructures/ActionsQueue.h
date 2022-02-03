// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Actions/AtomicActions/AtomicAction.h"
#include "ActionsQueue.generated.h"

/// <summary>
/// Queue that elements only can pop actions when unit times are 0.
/// Every action in atomicActionsQueue action has a unit time asociated in timeUnits variable in the same index
/// </summary>
UCLASS()
class MYD_API UActionsQueue : public UObject
{
	GENERATED_BODY()

private: TArray<UAtomicAction*> atomicActionsQueue;
private: TArray<float*> timeUnits;

public: UActionsQueue();

public: void Push(UAtomicAction* queuedAction, float unitTime);
public: TArray<UAtomicAction*> Pop();
public: void UpdateTimeUnits(float timeUnitsElapsed);
public: void Empty();
};
