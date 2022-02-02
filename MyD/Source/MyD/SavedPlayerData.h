// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEditor/EnumRol.h"
#include "Actions/Action.h"
#include "SavedPlayerData.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class MYD_API USavedPlayerData: public UObject
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int hp = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int armor = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicArmor = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int damage = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		UTexture2D* iconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TEnumAsByte<Rol> playerRol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UAction> playerActions;



public: UFUNCTION(BlueprintCallable) int GetHP() { return hp; };
public: UFUNCTION(BlueprintCallable) int GetArmor() { return armor; };
public: UFUNCTION(BlueprintCallable) int GetMagicArmor() { return magicArmor; };
public: UFUNCTION(BlueprintCallable) int GetDamage() { return damage; };
public: UFUNCTION(BlueprintCallable) int GetMagicDamage() { return magicDamage; };
public: UFUNCTION(BlueprintCallable) UTexture2D* GetIcon() { return iconTexture; };
public: UFUNCTION(BlueprintCallable) TEnumAsByte<Rol> GetRol() { return playerRol; };
public: UFUNCTION(BlueprintCallable) TSubclassOf<UAction> GetActions() { return playerActions; };

public: UFUNCTION(BlueprintCallable) void SetHP(int _hp)
{

	if (_hp > 19)
	{
		hp = 19;
	}
	else if (_hp < 1)
	{
		hp = 1;
	}
	else
	{
		hp = _hp;
	}
};
public: UFUNCTION(BlueprintCallable) void SetArmor(int _armor) {

	if (_armor > 19)
	{
		armor = 19;
	}
	else if (_armor < 1)
	{
		armor = 1;
	}
	else
	{
		armor = _armor;
	}
};
public: UFUNCTION(BlueprintCallable) void SetMagicArmor(int _magicArmor) {

	if (_magicArmor > 19)
	{
		magicArmor = 19;
	}
	else if (_magicArmor < 1)
	{
		magicArmor = 1;
	}
	else
	{
		magicArmor = _magicArmor;
	}
};
public: UFUNCTION(BlueprintCallable) void SetDamage(int _damage) {

	if (_damage > 19)
	{
		damage = 19;
	}
	else if (_damage < 1)
	{
		damage = 1;
	}
	else
	{
		damage = _damage;
	}
};
public: UFUNCTION(BlueprintCallable) void SetMagicDamage(int _magicDamage) {

	if (_magicDamage > 19)
	{
		magicDamage = 19;
	}
	else if (_magicDamage < 1)
	{
		magicDamage = 1;
	}
	else
	{
		magicDamage = _magicDamage;
	}
};
public: UFUNCTION(BlueprintCallable) void SetIconTexture(UTexture2D* _icon) { iconTexture = _icon; };
public: UFUNCTION(BlueprintCallable) void SetRol(TEnumAsByte<Rol> _rol) { playerRol = _rol; };
public: UFUNCTION(BlueprintCallable) void SetActions(TSubclassOf<UAction> _actions) { playerActions = _actions; };

	  UFUNCTION(BlueprintCallable)
		USavedPlayerData* USavedPlayerDataInit();


USavedPlayerData();
};
