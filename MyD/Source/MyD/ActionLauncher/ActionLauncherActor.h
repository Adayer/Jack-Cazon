// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionLauncherComponent.h"
#include "ActionLauncherActor.generated.h"

UCLASS()
class MYD_API AActionLauncherActor : public AActor
{
	GENERATED_BODY()

private: UPROPERTY() UActionLauncherComponent* actionLauncherComponent;
private: UPROPERTY(EditAnywhere) ACharacterActor* actionLauncherCharacter;
private: UPROPERTY(EditAnywhere) AHexCell* actionRecieverCell;
	
public:	
	// Sets default values for this actor's properties
	AActionLauncherActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: UFUNCTION(BlueprintCallable) void ExecuteAction();
};
