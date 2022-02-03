// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonAction.h"
#include "../Cells/HexCell.h"
#include "../CharacterActor.h"
#include "AtomicActions/DamageAtomicAction.h"

bool UPoisonAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	if (actionRecieverCell->GetCharacterInCell() != nullptr && actionRecieverCell->GetCharacterInCell()->GetTeam() != actionLauncherCharacter->GetTeam()) {
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No enemy in selected cell"));
	return false;
}

void UPoisonAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	actionRecieverCell->GetCharacterInCell()->AddStartingTurnActionRepeatable(NewObject<UDamageAtomicAction>(), 3);
	UE_LOG(LogTemp, Warning, TEXT("Poision Action Executed"));
}