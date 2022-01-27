// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../CharacterActor.h"
#include "TurnOrderData.h"
#include "CombatInitiativeWidget.h"
#include "CombatGameMode.generated.h"

/**
 * 
 */
UENUM()
enum CombatPhase
{
	Invalid = -1,
	StartingCombat,
	StartingTurn,
	WaitingForEndTurn,
	EndingTurn,
	EndingCombat,
	Count
};
UCLASS()
class MYD_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

	//Variables and Properties
public:
	//UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UCombatInitiativeWidget> combatInitiativeWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
		unsigned int NUM_PLAYERS = 4;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		UCombatInitiativeWidget* combatInitiativeWidget;

	//Logic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category="Combat")
		TArray<UTurnOrderData*> turnOrderDataList;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		int roundIndex; //Ronda actual (una ronda se compone de varios turnos)
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		int turnIndex; //Turno actual
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		TEnumAsByte<CombatPhase> currentCombatPhase;
	//Functions
public:
	UFUNCTION(BlueprintCallable, Category="Combat")
		void SetCombatOrder(); //Called at start of combat to set the initiative order
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void StartTurn(); //Called to start the next turn of initiative
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void EndTurn(); //Called when turn ends to set up the next one
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void EndCombat(); //Called when combat ends
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void StartCombat(); //Called to StartCombat
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void ContinueCombat(); //Called to move to the next phase of combat

	//UI
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void ToggleInitiativeUI();
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void UpdateInitiativeUI();
protected:
	void BeginPlay() override;
private:
};
