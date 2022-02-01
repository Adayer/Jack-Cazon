// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEditor/EnumRol.h"
#include "GameFramework/Character.h"
#include "DataStructures/ActionsQueue.h"
#include "CharacterActor.generated.h"

class AHexCell;
class UAction;

UCLASS()
class MYD_API ACharacterActor : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterActor();
private: 
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int hp = 10;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		int currentHp = hp;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int armor = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicArmor = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int damage = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicDamage = 10;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int movement;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int numActions;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		int attackRange;
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		bool team;


public:
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		AHexCell* myCell;

/// <summary>
/// Actions executed at the start of character's turn
/// </summary>
private: UPROPERTY(VisibleAnywhere, Category = "Attributes") UActionsQueue* startTurnActions;

/// <summary>
/// Actions executed every Tick function call
/// </summary>
private: UPROPERTY(VisibleAnywhere, Category = "Attributes") UActionsQueue* tickActions;

public: 
	//////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		UTexture2D* iconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TEnumAsByte<Rol> playerRol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UAction> playerActions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/////////////////////////////
	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
		void StartTurn();

public: UFUNCTION() void RecieveDamage(int32 damageAmount);
public: UFUNCTION() void RecieveMagicDamage(int32 damageAmount);
public: UFUNCTION() void RecieveDirectDamage(int32 damageAmount);
public: UFUNCTION() void RecieveHealing(int32 healAmount);
public: UFUNCTION() void Block();
public: UFUNCTION()	void ModifyArmor(int armorVariation);
private: UFUNCTION() void Die();

public: UFUNCTION() void AddStartingTurnAction(UAtomicAction* startingTurnAction, int turnsLeftToExecuteAction);
public: UFUNCTION() void AddStartingTurnActionRepeatable(UAtomicAction* startingTurnAction, int numTurnsExecutingAction);
public: UFUNCTION() void AddTickAction(UAtomicAction* tickAction, float secondsToExecuteAction);

public: UFUNCTION() int32 GetAttackPower();
public: UFUNCTION() int32 GetMagicAttackPower();
public: UFUNCTION() int GetAttackRange();
public: UFUNCTION() int GetMovementRange();

public: AHexCell* GetMyCell();
public: void SetCharacterCell(AHexCell* myNewCell);

public:
	UFUNCTION()
		int GetCurrentHP() { return currentHp; }
	UFUNCTION(BlueprintCallable, Category="Combat")
		bool GetTeam() { return team; }
	UFUNCTION()
		void SetTeam(bool _team) { team = _team; }

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

};
