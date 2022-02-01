// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifyArmorAtomicAction.h"

#include "../../CharacterActor.h"

void UModifyArmorAtomicAction::ExecuteAtomicAction(ACharacterActor* actionRecieverCharacter) {
	actionRecieverCharacter->ModifyArmor(armorVariation);
	UE_LOG(LogTemp, Warning, TEXT("Armor modified"));
}