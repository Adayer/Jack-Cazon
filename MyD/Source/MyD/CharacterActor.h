// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterActor.generated.h"

class AHexCell;

UCLASS()
class MYD_API ACharacterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterActor();

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int hp;
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int armor;
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int damage;

	UPROPERTY(EditAnywhere, Category = "Attributes")
		int movement;



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

	/////////////////////////////
	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
		void StartTurn();

public: UFUNCTION() void RecieveDamage(int32 damageAmount);

public: UFUNCTION() int32 GetAttackPower();
public: UFUNCTION() int GetAttackRange();

};
