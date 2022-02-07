// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionsQueue.h"

UActionsQueue::UActionsQueue() {
	atomicActionsQueue = TArray<UAtomicAction*>();
	timeUnits = TArray<float*>();
}

void UActionsQueue::Push(UAtomicAction* queuedAction, float unitTime)
{
	if (queuedAction != nullptr) {
		atomicActionsQueue.Add(queuedAction);
		timeUnits.Add(new float(unitTime));
	}

	ensureMsgf(atomicActionsQueue.Num() == timeUnits.Num(), TEXT("There is no the same number of elements in atomicActionsQueue and timeUnits"));
}

TArray<UAtomicAction*> UActionsQueue::Pop() {
	TArray<UAtomicAction*> returnedActions;

	int popedActions = 0;
	for (int i = 0; i < atomicActionsQueue.Num(); ++i) {
		if (*timeUnits[i] <= 0.001f) { //Errores de redondeo
			returnedActions.Add(atomicActionsQueue[i]);

			atomicActionsQueue.RemoveAt(i - popedActions);
			timeUnits.RemoveAt(i - popedActions);
			++popedActions;
		}
	}

	return returnedActions;
}

void UActionsQueue::UpdateTimeUnits(float timeUnitsElapsed)
{
	for (float* timeUnit : timeUnits) {
		*timeUnit = FMath::Max<float>(0, *timeUnit - timeUnitsElapsed);
	}
}

void UActionsQueue::Empty()
{
	atomicActionsQueue.Empty();
	timeUnits.Empty();
}