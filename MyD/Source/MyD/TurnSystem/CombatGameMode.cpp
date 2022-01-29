// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatGameMode.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatGameMode::StartCombat()
{
	currentCombatPhase = CombatPhase::StartingCombat;
	turnIndex = 0;
	roundIndex = 0;
	SetCombatOrder();
	ToggleInitiativeUI();
	ContinueCombat();
}

void ACombatGameMode::SetCombatOrder()
{
	TArray<AActor*> bufferActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterActor::StaticClass(), bufferActors);//Cambiar clase de personaje

	unsigned int numCharacters = bufferActors.Num();
	turnOrderDataList.Empty();
	for (unsigned int i = 0; i < numCharacters; ++i)
	{
		ACharacterActor* bufferChar = Cast<ACharacterActor>(bufferActors[i]);//Cambiar clase de personaje
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
			StartTurn(); //Mirar si estar recursividad la lia
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
	UpdateInitiativeUI();
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

void ACombatGameMode::ToggleInitiativeUI()
{
	if (combatInitiativeWidget)
	{
		if (combatInitiativeWidget->IsInViewport())
		{
			combatInitiativeWidget->RemoveFromViewport();
		}
		combatInitiativeWidget = nullptr;
	}
	else
	{
		combatInitiativeWidget = CreateWidget<UCombatInitiativeWidget>(GetWorld(), combatInitiativeWidgetClass);
		combatInitiativeWidget->InitUI();
		combatInitiativeWidget->AddToViewport();
	}
}

void ACombatGameMode::UpdateInitiativeUI()
{
	if (combatInitiativeWidget)
	{
		combatInitiativeWidget->NextTurn();
	}
}