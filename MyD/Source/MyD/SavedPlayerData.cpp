// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedPlayerData.h"

USavedPlayerData* USavedPlayerData::USavedPlayerDataInit() {
	hp = 10;
	armor = 10;
	magicArmor = 10;
	damage = 10;
	magicDamage = 10;

	return this;
}

USavedPlayerData::USavedPlayerData() {
	hp = 10;
	armor = 10;
	magicArmor = 10;
	damage = 10;
	magicDamage = 10;

}

USavedPlayerData* USavedPlayerData::GetItem() {


	return this;
}
