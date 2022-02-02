// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatInitiativeIconWidget.h"
#include "CombatInitiativeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UCombatInitiativeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UCombatInitiativeIconWidget> combatInitiativeIconClass;
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void NextTurn();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void InitUI();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void RemoveDeadChar(int index);
};
