// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexCell.h"
#include "TestAIController.h"
#include "GridManager.generated.h"

UCLASS()
class MYD_API AGridManager : public AActor
{
	GENERATED_BODY()
	
	///////////////////////////////////////////////////////////
public:
	UPROPERTY(EditAnywhere)
		APawn* testPawn;

	ATestAIController* controller;
	////////////////////////////////////////////////////////////
protected:
	UPROPERTY(EditAnywhere)
		int gridWidth;

	UPROPERTY(EditAnywhere)
		int gridHeight;


	UPROPERTY(EditAnywhere)
		TSubclassOf<AHexCell> BaseCell;


	float XOffset=86.5f;
	float YOffset=75.f;
	float OddOffset=43.25f;

public: //Quitar este public
	TArray<TArray<AHexCell*>> gridArray;

private:
	AHexCell* lastCell = NULL;

public:	
	// Sets default values for this actor's properties
	AGridManager();

	UFUNCTION(BlueprintCallable)
		void SpawnCells();

	void OnHoverCell(AHexCell* Cell);
	//////////////////////////////////////////////////////////////////////////////
	void MovePawn();
	/////////////////////////////////////////////////////////////////////////////


private:
	TArray<AHexCell*> path;
	bool AStar(AHexCell* start, AHexCell* end, float maxSteps);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
