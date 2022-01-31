// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomicAction.h"

bool UAtomicAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	return true;
}

void UAtomicAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	UE_LOG(LogTemp, Warning, TEXT("This is the base clase for making ATOMIC actions, override ExecuteAction & CanExecuteAction methods to create new ATOMIC action effects"));
}
