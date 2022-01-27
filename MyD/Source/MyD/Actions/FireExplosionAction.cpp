// Fill out your copyright notice in the Description page of Project Settings.


#include "FireExplosionAction.h"

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
			ApplyFireDamage(actionRecieverCharacter);
		}
	}
}

void UFireExplosionAction::ApplyFireDamage(ACharacterActor* actionRecieverCharacter) {

}