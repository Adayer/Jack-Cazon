// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Cells/HexCell.h"
#include "TestAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API ATestAIController : public AAIController
{
	GENERATED_BODY()


public:
	ATestAIController();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	
};
