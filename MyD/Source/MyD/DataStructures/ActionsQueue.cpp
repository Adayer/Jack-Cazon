// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionsQueue.h"

void UActionsQueue::Push(UAtomicAction* queuedAction, float unitTime)
{
	if (queuedAction != nullptr) {
		atomicActionsQueue.Add(queuedAction);
		timeUnits.Add(unitTime);
	}

	ensureMsgf(atomicActionsQueue.Num() == timeUnits.Num(), TEXT("There is no the same number of elements in atomicActionsQueue and timeUnits"));
}

TArray<UAtomicAction*> UActionsQueue::Pop() {
	TArray<UAtomicAction*> returnedActions = TArray<UAtomicAction*>();

	int popedActions = 0;
	for (int i = 0; i < atomicActionsQueue.Num(); ++i) {
		if (timeUnits[i] == 0) {
			returnedActions.Add(atomicActionsQueue[i]);

			atomicActionsQueue.RemoveAt(i - popedActions);
			timeUnits.RemoveAt(i - popedActions);
			++popedActions;
		}
	}

	return returnedActions;
}
