// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Cells/HexCell.h"
#include "ActionLauncher/ActionLauncherActor.h"
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
		UPROPERTY(Transient) AGridManager* Grid;
		UPROPERTY() bool Walking = false;
		UPROPERTY(Transient) TArray<AHexCell*> path;
		UPROPERTY() float cooldown = 0;
		UPROPERTY(Transient) AHexCell* currentCell;

private: UPROPERTY(Transient) AActionLauncherActor* actionLauncher;
private: UPROPERTY(Transient) TArray<AHexCell*> affectedCells;
private: UPROPERTY(Transient) AHexCell* selectedCell;
private: UPROPERTY() bool preparingAction = false;

public:
	AMyController();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void MoveCharacter(TArray<AHexCell*>& _path);

public: void ResetSelectedCells();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupInputComponent() override;

public: UFUNCTION() void OnLeftMouseButtonPressed();

public: UFUNCTION(BlueprintCallable, Category = "Combat") TArray<AHexCell*> GetAffectedCells();
public: UFUNCTION(BlueprintCallable, Category = "Combat") AHexCell* GetSelectedCell();

public: UFUNCTION(BlueprintCallable, Category = "Combat") void PrepareAction(UAction* actionToExecute, ACharacterActor* actionLauncherCharacter);
};
