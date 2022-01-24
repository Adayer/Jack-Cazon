// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresPruebasCharacter.h"

// Sets default values
AAndresPruebasCharacter::AAndresPruebasCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAndresPruebasCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAndresPruebasCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAndresPruebasCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAndresPruebasCharacter::StartTurn_Implementation()
{

}

