// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SavedPlayerData.h"
#include "MainGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class MYD_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<USavedPlayerData*> playersData;

		UMainGameInstance();
};
