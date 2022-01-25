// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Actions/Action.h"
#include "../BoardCharacter.h"
#include "ActionLauncherComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYD_API UActionLauncherComponent : public UActorComponent
{
	GENERATED_BODY()

public: UPROPERTY() UAction* myAction;

public:	
	// Sets default values for this component's properties
	UActionLauncherComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: UFUNCTION() bool ExecuteAction(ABoardCharacter* actionLauncherCharacter, ABoardCharacter* actionRecieverCharacter);
};