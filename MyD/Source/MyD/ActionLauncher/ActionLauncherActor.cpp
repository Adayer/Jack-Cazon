// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionLauncherActor.h"

// Sets default values
AActionLauncherActor::AActionLauncherActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	actionLauncherComponent = CreateDefaultSubobject<UActionLauncherComponent>("actionLauncherComponent");
}

// Called when the game starts or when spawned
void AActionLauncherActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AActionLauncherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActionLauncherActor::ExecuteAction() {
	actionLauncherComponent->ExecuteAction(actionLauncherCharacter, actionRecieverCell);
}

void AActionLauncherActor::SetActionLaunchersAction(UAction* newAction)
{
	actionLauncherComponent->SetMyAction(newAction);
}

void AActionLauncherActor::SetActionLauncherCharacter(ACharacterActor* newActionLauncherCharacter)
{
	actionLauncherCharacter = newActionLauncherCharacter;
}

ACharacterActor* AActionLauncherActor::GetActionLauncherCharacter()
{
	return actionLauncherCharacter;
}

UFUNCTION(BlueprintCallable) void AActionLauncherActor::SetActionRecieverCell(AHexCell* newActionRecieverCell)
{
	actionRecieverCell = newActionRecieverCell;
}

UFUNCTION(BlueprintCallable)AHexCell* AActionLauncherActor::GetActionRecieverCell()
{
	return actionRecieverCell;
}

