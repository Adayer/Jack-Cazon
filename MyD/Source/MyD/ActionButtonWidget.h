// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYD_API UActionButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected: UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ActionButton;
};
