// Fill out your copyright notice in the Description page of Project Settings.


#include "FireExplosionAction.h"
#include "../CharacterActor.h"
#include "../Cells/HexCell.h"


bool UFireExplosionAction::CanExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	return true;
}

void UFireExplosionAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {
	TArray<AHexCell*> affectedCells = TArray<AHexCell*>();
	affectedCells.Add(actionRecieverCell);
	affectedCells.Append(actionRecieverCell->neighbours);

	ACharacterActor* actionRecieverCharacter = nullptr;
	for (AHexCell* affectedCell : affectedCells) {
		actionRecieverCharacter = affectedCell->GetCharacterInCell();
		if (actionRecieverCharacter != nullptr) {
			actionRecieverCharacter->RecieveMagicDamage(actionLauncherCharacter->GetMagicAttackPower());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Fire attack action executed"));
}

TArray<AHexCell*> UFireExplosionAction::GetAffectedCells(AHexCell* actionRecieverCell) {
	TArray<AHexCell*> returnedCells;

	returnedCells.Add(actionRecieverCell);
	returnedCells.Append(actionRecieverCell->neighbours);

	return returnedCells;
}

bool UFireExplosionAction::IsActionInRangeOfExecution(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	
	if (actionRecieverCell->GetCharacterInCell() != nullptr) {
		return actionLauncherCharacter->GetTeam() != actionRecieverCell->GetCharacterInCell()->GetTeam();
	}

	return true;
}