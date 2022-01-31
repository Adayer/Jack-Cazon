// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class AHexCell;

UCLASS()
class MYD_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();
	
	UPROPERTY(EditAnywhere)
	AHexCell* cellOwner;
	bool team = false;

	UPROPERTY(EditAnywhere)
		UMaterial* aTeamMat;

	UPROPERTY(EditAnywhere)
		UMaterial* bTeamMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* staticMesh;

	void SetPoint(bool _team, AHexCell* cell);

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
