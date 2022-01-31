// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEditor/EnumRol.h"
#include "GameFramework/Character.h"
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

private:
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		AHexCell* myCell;


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
public: UFUNCTION() void RecieveHealing(int32 healAmount);
public: UFUNCTION() void Block();
private: UFUNCTION() void Die();

public: UFUNCTION() int32 GetAttackPower();
public: UFUNCTION() int32 GetMagicAttackPower();
public: UFUNCTION() int GetAttackRange();

	  UFUNCTION()
		  void SetIconTexture(UTexture2D* _texture) { iconTexture = _texture; }

public: AHexCell* GetMyCell();
public: void SetCharacterCell(AHexCell* myNewCell);

};
