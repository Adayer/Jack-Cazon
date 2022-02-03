// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"
#include "../CharacterActor.h"
#include "../Cells/HexCell.h"


bool UAttackAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
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

void UAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionRecieverCell->GetCharacterInCell()->RecieveDamage(actionLauncherCharacter->GetAttackPower());
	UE_LOG(LogTemp, Warning, TEXT("Attack action realized"));
}

bool UAttackAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	UE_LOG(LogTemp, Warning, TEXT("Objetive cell is out of range"));

	if (actionLauncherCharacter->GetMyCell()->DistanceToCell(actionRecieverCell) > actionLauncherCharacter->GetAttackRange()) {
		UE_LOG(LogTemp, Warning, TEXT("attacked character out of attack range"));
		return false;
	}

	return true;
}