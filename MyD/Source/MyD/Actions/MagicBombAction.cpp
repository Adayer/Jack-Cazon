// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBombAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include "AtomicActions/MagicDamageAtomicAction.h"

bool UMagicBombAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr && actionLauncherCharacter->GetTeam() != actionRecieverCell->GetCharacterInCell()->GetTeam()) {
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No enemy in selected cell"));
	return false;
}

void UMagicBombAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	UMagicDamageAtomicAction* magicDamageAtomicAction = NewObject<UMagicDamageAtomicAction>();;
	magicDamageAtomicAction->reciebedDamage = actionLauncherCharacter->GetMagicDamage() * 2;

	actionLauncherCharacter->AddStartingTurnAction(magicDamageAtomicAction, 2);
	UE_LOG(LogTemp, Warning, TEXT("Magic bomb action realized"));
}

bool UMagicBombAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return actionRecieverCell->GetCharacterInCell()->GetTeam() != actionLauncherCharacter->GetTeam();
	}
	
	return false;
}