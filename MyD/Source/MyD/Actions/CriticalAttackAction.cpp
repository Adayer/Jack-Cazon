// Fill out your copyright notice in the Description page of Project Settings.


#include "CriticalAttackAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"

bool UCriticalAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	if (actionRecieverCell->GetCharacterInCell() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No character in cell selected"));
		return false;
	}
	else if (actionRecieverCell->GetCharacterInCell()->GetTeam() == actionLauncherCharacter->GetTeam()) {
		UE_LOG(LogTemp, Warning, TEXT("Character selected is a team mate :("));
		return false;
	}

	return true;
}

void UCriticalAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	int32 isCritticAttck = FMath::RandRange(0, 2);

	if (isCritticAttck == 0) {
		actionRecieverCell->GetCharacterInCell()->RecieveDamage(actionLauncherCharacter->GetAttackPower() * 2);
		UE_LOG(LogTemp, Warning, TEXT("Critic attack action realized"));
	}
	else {
		actionRecieverCell->GetCharacterInCell()->RecieveDamage(actionLauncherCharacter->GetAttackPower());
		UE_LOG(LogTemp, Warning, TEXT("Attack action realized"));
	}
	
	
}

bool UCriticalAttackAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetAttackRange()) {
		UE_LOG(LogTemp, Warning, TEXT("attacked character out of attack range"));
		return false;
	}

	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return actionRecieverCell->GetCharacterInCell()->GetTeam() != actionLauncherCharacter->GetTeam();
	}

	return true;
}