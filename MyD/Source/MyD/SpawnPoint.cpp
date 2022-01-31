// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Cells/HexCell.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	staticMesh->SetupAttachment(RootComponent);

}

//// Called when the game starts or when spawned
//void ASpawnPoint::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ASpawnPoint::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//

void ASpawnPoint::SetPoint(bool _team, AHexCell* cell)
{
	if (_team)
	{
		staticMesh->SetMaterial(0, bTeamMat);
	}
	else
	{
		staticMesh->SetMaterial(0, aTeamMat);
	}

	team = _team;
	cellOwner = cell;
}
