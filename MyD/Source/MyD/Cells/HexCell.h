// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexCell.generated.h"

class ACharacterActor;

UENUM()
enum class ECellType : uint8
{
	Base

};

class UStaticMeshComponent;

UCLASS()
class MYD_API AHexCell : public AActor
{
	GENERATED_BODY()


public:
	FIntPoint hexCoord;

/////////////////////////////////////////////
//		A STAR PROPERTIES
////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) //Asociar a tipo de celda?
		int weight = 1;

	AHexCell* parent = NULL;
	bool visited = false;
	bool free = true;
	TArray<AHexCell*> neighbours;
	float globalGoal = INFINITY;
	float localGoal = INFINITY;


	/////////////////////////////////////////

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ECellType cellType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* cellMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* defaultMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* validMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* invalidMat;

	///Too ADD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ACharacterActor* characterInCell;
	
public:	
	// Sets default values for this actor's properties
	AHexCell();

	void ChangeMaterial(bool valid);
	void ResetMaterial();
	void ResetAStartProperties();

public: UFUNCTION() ACharacterActor* GetCharacterInCell();
public: UFUNCTION() void SetCharacterInCell(ACharacterActor* newCharacterInCell);

public: int DistanceToCell(AHexCell* otherCell);

};
