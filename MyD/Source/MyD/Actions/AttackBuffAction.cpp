// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBuffAction.h"

#include "../CharacterActor.h"
#include "../Cells/HexCell.h"
#include <MyD/Actions/AtomicActions/ReduceDamageAtomicAction.h>

void UAttackBuffAction::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell) {

	int attackUpgrade = actionLauncherCharacter->GetDamage() / 2;
	actionLauncherCharacter->Modifyattack(attackUpgrade);
	UReduceDamageAtomicAction* attackReduction = NewObject<UReduceDamageAtomicAction>();
	attackReduction->damageVariation = -attackUpgrade;
	actionLauncherCharacter->AddStartingTurnAction(attackReduction, 1);
	UE_LOG(LogTemp, Warning, TEXT("Attack buff action realized"));
}