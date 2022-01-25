// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyController.generated.h"

/**
 * 
 */

class AGridManager;

UCLASS()
class MYD_API AMyController : public APlayerController
{
	GENERATED_BODY()

private:
		AGridManager* Grid;

public:
	AMyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
