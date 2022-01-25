// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BoardCharacter.generated.h"

UCLASS()
class MYD_API ABoardCharacter : public ACharacter
{
	GENERATED_BODY()

private: UPROPERTY(VisibleAnywhere, Category = "Board Character") int32 health;
private: UPROPERTY(VisibleAnywhere, Category = "Board Character") int32 defense;
private: UPROPERTY(VisibleAnywhere, Category = "Board Character") int32 attackPower;
private: UPROPERTY(VisibleAnywhere, Category = "Board Character") float attackRange;

public:
	// Sets default values for this character's properties
	ABoardCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: UFUNCTION() void RecieveDamage(int32 damageAmount);

public: UFUNCTION() int32 GetAttackPower();
public: UFUNCTION() float GetAttackRange();
};
