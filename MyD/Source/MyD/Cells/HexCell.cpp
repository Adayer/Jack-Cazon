// Fill out your copyright notice in the Description page of Project Settings.


#include "HexCell.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include "../CharacterActor.h"

// Sets default values
AHexCell::AHexCell()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	cellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));

	cellMesh->SetupAttachment(RootComponent);

}

void AHexCell::ChangeMaterial(bool valid)
{
	if (valid)
	{
		cellMesh->SetMaterial(0, validMat);
	}
	else
	{
		cellMesh->SetMaterial(0, invalidMat);
	}
}

void AHexCell::ResetMaterial()
{
	cellMesh->SetMaterial(0, defaultMat);
}

void AHexCell::ResetAStartProperties()
{
	parent = NULL;
	visited = false;
	globalGoal = INFINITY;
	localGoal = INFINITY;
}

ACharacterActor* AHexCell::GetCharacterInCell()
{
	return characterInCell;
}

void AHexCell::SetCharacterInCell(ACharacterActor* newCharacterInCell)
{
	characterInCell = newCharacterInCell;
}
