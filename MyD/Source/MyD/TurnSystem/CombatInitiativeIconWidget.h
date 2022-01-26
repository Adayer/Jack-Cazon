// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnOrderData.h"
#include "CombatInitiativeIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UCombatInitiativeIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TWeakObjectPtr<UTurnOrderData> turnOrderData;
};
