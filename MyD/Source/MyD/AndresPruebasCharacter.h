// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AndresPruebasCharacter.generated.h"

UCLASS()
class MYD_API AAndresPruebasCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAndresPruebasCharacter();

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

	UFUNCTION(BlueprintNativeEvent, Category="Combat")
		void StartTurn();

};
