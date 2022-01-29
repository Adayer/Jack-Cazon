// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEditor/EnumRol.h"
#include "Actions/Action.h"
#include "GameFramework/Character.h"
#include "CharacterActor.generated.h"

class AHexCell;

UCLASS()
class MYD_API ACharacterActor : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
		int hp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Atributes")
		int currentHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
		int damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
		int magicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
		int armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
		int magicArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Atributes)
		TArray<UAction*> Actions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Atributes)
		TEnumAsByte<Rol> Rol;		
	



	//////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		UTexture2D* iconTexture;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int numActions;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		int attackRange;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
		AHexCell* myCell;


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

public: UFUNCTION() int32 GetAttackPower();
public: UFUNCTION() int32 GetMagicAttackPower();
public: UFUNCTION() int GetAttackRange();

	  UFUNCTION()
		  void SetIconTexture(UTexture2D* _texture) { iconTexture = _texture; }

};
