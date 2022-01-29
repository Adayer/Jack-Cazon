// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Cells/HexCell.h"
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
		bool Walking = false;
		TArray<AHexCell*> path;
		float cooldown = 0;
		AHexCell* currentCell;

public:
	AMyController();
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void MoveCharacter(TArray<AHexCell*>& _path);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
