// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Cells/HexCell.h"
#include "../MyController.h"
#include "../CharacterActor.h"
#include "GridManager.generated.h"

UCLASS()
class MYD_API AGridManager : public AActor
{
	GENERATED_BODY()
	
	///////////////////////////////////////////////////////////
public:
	AMyController* controller;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACharacterActor> CharacterBPClass;

	UPROPERTY(EditAnywhere)
		UMaterial* aTeamMat;

	UPROPERTY(EditAnywhere)
		UMaterial* bTeamMat;

	UPROPERTY(EditAnywhere)
		UStaticMesh* archerMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* tankMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* magueMesh;


	////////////////////////////////////////////////////////////
protected:


	UPROPERTY(EditAnywhere)
	UTexture2D* ArcherTextureObject;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* TankTextureObject;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* MagueTextureObject;
	


private:
	AHexCell* lastCell = NULL;

public:	
	// Sets default values for this actor's properties
	AGridManager();

	UFUNCTION(BlueprintCallable)
		void SpawnCharacters();

	void OnHoverCell(AHexCell* cell, TArray<AHexCell*> ignoreCells = TArray<AHexCell*>());
	//////////////////////////////////////////////////////////////////////////////
	void MovePawn();
	/////////////////////////////////////////////////////////////////////////////

	bool PutCharacterInCell(ACharacterActor* placedCharacter, AHexCell* targetCell);

private:
	TArray<AHexCell*> path;
	bool AStar(AHexCell* start, AHexCell* end, float maxSteps);

public: TArray<AHexCell*>* GetAStarPath(AHexCell* start, AHexCell* end, float maxSteps);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
