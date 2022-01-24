// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HexCell.h"
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
	void WalkPath(TArray<AHexCell*>* _path);

	AHexCell* currentCell;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool walking = false;
	TArray<AHexCell*>* path;
	float cooldown = 0;
};
