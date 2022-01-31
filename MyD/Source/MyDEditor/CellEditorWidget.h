// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include <MyD/Cells/HexCell.h>
#include <MyD/SpawnPoint.h>
#include "CellEditorWidget.generated.h"


/**
 * 
 */
class AHexCell;

UCLASS()
class MYDEDITOR_API UCellEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()	

	float XOffset = 86.5f;
	float YOffset = 75.f;
	float OddOffset = 43.25f;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHexCell> BaseCell;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpawnPoint> spawnPoint;

	UFUNCTION(BlueprintCallable)
	void CreateCells(int gridWidth, int gridHeight);

	UFUNCTION(BlueprintCallable)
		void CreateSpawnPoint(bool team);

	UFUNCTION(BlueprintCallable)
	void ChangeCellType(ECellType type); //El enum esta definido?

	//		M A T E R I A L S
	UPROPERTY(EditAnywhere)
		UMaterial* defaultMat;

	UPROPERTY(EditAnywhere)
		UMaterial* waterMat;

	UPROPERTY(EditAnywhere)
		UMaterial* obstacleMat;

};
