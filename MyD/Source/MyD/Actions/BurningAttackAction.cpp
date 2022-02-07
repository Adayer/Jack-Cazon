// Fill out your copyright notice in the Description page of Project Settings.


#include "BurningAttackAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include <MyD/Actions/AtomicActions/DamageAtomicAction.h>

void UBurningAttackAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	actionRecieverCell->GetCharacterInCell()->AddStartingTurnAction(NewObject<UDamageAtomicAction>(), 1);
	Super::ExecuteAction(actionLauncherCharacter, actionRecieverCell);

	UE_LOG(LogTemp, Warning, TEXT("Burning attack action realized"));
}