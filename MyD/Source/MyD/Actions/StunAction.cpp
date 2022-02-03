// Fill out your copyright notice in the Description page of Project Settings.


#include "StunAction.h"
#include "../CharacterActor.h"
#include "../Cells/HexCell.h"

bool UStunAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No enemy in selected cell"));
	return false;
}


void UStunAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	actionRecieverCell->GetCharacterInCell()->GetStunned(3);

}

bool UStunAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return actionRecieverCell->GetCharacterInCell()->GetTeam() != actionLauncherCharacter->GetTeam();
	}

	return false;
}
