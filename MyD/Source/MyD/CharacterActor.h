// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataStructures/ActionsQueue.h"
#include "CharacterActor.generated.h"

class AHexCell;

UCLASS()
class MYD_API ACharacterActor : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterActor();

private: 
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int hp;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		int currentHp;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int armor;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicArmor;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int damage;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int magicDamage;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int movement;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int numActions;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		int attackRange;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		UTexture2D* iconTexture;



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

	  UFUNCTION()
		  void SetIconTexture(UTexture2D* _texture) { iconTexture = _texture; }

public: AHexCell* GetMyCell();
public: void SetCharacterCell(AHexCell* myNewCell);

};
