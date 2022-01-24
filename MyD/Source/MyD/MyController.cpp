// Fill out your copyright notice in the Description page of Project Settings.


#include "MyController.h"
#include "HexCell.h"
#include "GridManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

AMyController::AMyController()
{
	SetActorTickEnabled(true);
}

void AMyController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	TArray<AActor*> foundArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AGridManager::StaticClass(), foundArray);
	if (foundArray.Num())
	{
		Grid = Cast<AGridManager>(foundArray[0]);
	}
}

void AMyController::Tick(float DeltaTime)
{
	FHitResult hitResult;
	if(GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult))
	{
		AHexCell* cell = Cast<AHexCell>(hitResult.Actor);
		if (cell)
		{
			Grid->OnHoverCell(cell);

			if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				Grid->MovePawn();
			}
		}

	}
}