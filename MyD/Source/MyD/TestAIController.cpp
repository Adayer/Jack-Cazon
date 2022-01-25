// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"
#include "GridManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ATestAIController::ATestAIController()
{
	SetActorTickEnabled(true);
}

void ATestAIController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	//Esta variable se tendría que setear desde otro lado

	TArray<AActor*> foundArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridManager::StaticClass(), foundArray);
	if (foundArray.Num())
	{
		currentCell = Cast<AGridManager>(foundArray[0])->gridArray[0][0];
	}

	GetPawn()->SetActorLocation(currentCell->GetActorLocation());
}

void ATestAIController::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(
	//	-1,        // don't over wrire previous message, add a new one
	//	0.55f,   // Duration of message - limits distance messages scroll onto screen
	//	FColor::Cyan.WithAlpha(64),   // Color and transparancy!
	//	FString::Printf(TEXT("        TryWalk "))  // Our usual text message format
	//);

	if (walking)
	{
		if (path->Num())
		{
			if (cooldown <= 0)
			{
				currentCell = path->Pop();
				GetPawn()->SetActorLocation(currentCell->GetActorLocation());
				cooldown = 0.5f;
			}
			else
			{
				cooldown -= DeltaTime;
			}
		}
		else
		{
			walking = false;
		}		
	}
}

void ATestAIController::WalkPath(TArray<AHexCell*>* _path)
{
	path = _path; //esto esta hecho super cutre, aedmas unavez que guarda el puntero no tendria que volver a pasarselo pero no me apetece pensar
	
	walking = true;
}