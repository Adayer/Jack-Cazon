// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AndresPruebasCharacter.h"

#include "TurnOrderData.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UTurnOrderData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		AAndresPruebasCharacter* character;
private:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		int initiative;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
		int tieBreakInitiative;
protected:
public:

	UTurnOrderData()
	{
		character = nullptr;
		initiative = -1;
		tieBreakInitiative = -1;
	}

	UFUNCTION(BlueprintCallable, Category="Combat")
		AAndresPruebasCharacter* GetCharacter() const { return character; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetCharacter(AAndresPruebasCharacter* _character) { character = _character; }
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
		int  GetInitiative() const { return initiative; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetInitiative(int _initiative) { initiative = _initiative; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		int  GetTieBreakInitiative() const { return tieBreakInitiative; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetTieBreakInitiative(int _initiative) { tieBreakInitiative = _initiative; }
};
