// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatGameMode.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartCombat();
}

void ACombatGameMode::StartCombat()
{
	currentCombatPhase = CombatPhase::StartingCombat;
	turnIndex = 0;
	roundIndex = 0;
	SetCombatOrder();
	ContinueCombat();
}

void ACombatGameMode::SetCombatOrder()
{
	TArray<AActor*> bufferActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAndresPruebasCharacter::StaticClass(), bufferActors);

	unsigned int numCharacters = bufferActors.Num();
	turnOrderDataList.Empty();
	for (unsigned int i = 0; i < numCharacters; ++i)
	{
		AAndresPruebasCharacter* bufferChar = Cast<AAndresPruebasCharacter>(bufferActors[i]);
		if (bufferChar)
		{
			int init = FMath::RandRange(1, 20);
			int tieBreak = FMath::RandRange(1, 1000);
			UTurnOrderData* newData = NewObject<UTurnOrderData>();
			newData->SetCharacter(bufferChar);
			newData->SetInitiative(init);
			newData->SetTieBreakInitiative(tieBreak);
			turnOrderDataList.Add(newData);
		}
	}
	//Sort by Initiative and in case of tie check who has the higher tiebreak
	turnOrderDataList.Sort([](UTurnOrderData& A, UTurnOrderData& B)
		{
			if (A.GetInitiative() < B.GetInitiative())
			{
				return true;
			}
			else if (A.GetInitiative() > B.GetInitiative())
			{
				return false;
			}
			else
			{
				return (A.GetTieBreakInitiative() <= B.GetTieBreakInitiative());
			}
		});
}

void ACombatGameMode::ContinueCombat()
{
	switch (currentCombatPhase)
	{
		case CombatPhase::StartingCombat:
		{
			currentCombatPhase = CombatPhase::StartingTurn;
			ContinueCombat(); //Mirar si estar recursividad la lia
			break;
		}
		case CombatPhase::StartingTurn:
		{
			StartTurn();
			break;
		}
		case CombatPhase::WaitingForEndTurn:
		{
			currentCombatPhase = CombatPhase::EndingTurn;
			EndTurn();
			break;
		}
		case CombatPhase::EndingTurn:
		{
			break;
		}
		case CombatPhase::EndingCombat:
		{
			break;
		}
		case CombatPhase::Invalid:
		{
			UE_LOG(LogTemp, Error, TEXT("COMBAT PHASE == INVALID!"));
			break;
		}
	}
}

void ACombatGameMode::StartTurn()
{
	currentCombatPhase = CombatPhase::WaitingForEndTurn;
	turnOrderDataList[turnIndex]->GetCharacter()->StartTurn();
}

void ACombatGameMode::EndTurn()
{
	//TODO:End of Combat Check
	//EndCombat();
	++turnIndex;
	if(turnIndex >= turnOrderDataList.Num())
	{ 
		turnIndex = 0;
	}
	currentCombatPhase = CombatPhase::StartingTurn;
	ContinueCombat();//Mirar si esta recursividad la lia o no
}

void ACombatGameMode::EndCombat()
{
	//TODO:End combat
}