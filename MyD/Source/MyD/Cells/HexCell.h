// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexCell.generated.h"

class ACharacterActor;

UENUM(BlueprintType)
enum class ECellType : uint8
{
	Base,
	Water,
	Sand,
	Obstacle
};

class UStaticMeshComponent;

UCLASS()
class MYD_API AHexCell : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere)
	FIntPoint hexCoord;

/////////////////////////////////////////////
//		A STAR PROPERTIES
////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere) 
		int weight = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ECellType cellType;

	AHexCell* parent = NULL;
	bool visited = false;

	UPROPERTY(EditAnywhere)
	TArray<AHexCell*> neighbours;
	float globalGoal = INFINITY;
	float localGoal = INFINITY;


	/////////////////////////////////////////


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* defaultMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* cellMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ACharacterActor* characterInCell;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* validMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterial* invalidMat;

	
public:	
	// Sets default values for this actor's properties
	AHexCell();

	void ChangeMaterial(bool valid);
	void ResetMaterial();
	void ResetAStartProperties();

	UFUNCTION() 
		ACharacterActor* GetCharacterInCell();
	UFUNCTION() 
		void SetCharacterInCell(ACharacterActor* newCharacterInCell);

	int DistanceToCell(AHexCell* otherCell);

};
