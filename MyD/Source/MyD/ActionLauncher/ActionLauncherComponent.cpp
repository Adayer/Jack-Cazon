// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionLauncherComponent.h"
#include "../Actions/AttackAction.h"
#include "../CharacterActor.h"
#include <MyD/TurnSystem/CombatGameMode.h>

// Sets default values for this component's properties
UActionLauncherComponent::UActionLauncherComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	myAction = CreateDefaultSubobject<UAttackAction>("myAction");
	
}


// Called when the game starts
void UActionLauncherComponent::BeginPlay()
{
	Super::BeginPlay();

	if (myAction == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("myAction begin play a NULL"));
		myAction = NewObject<UAttackAction>(UAttackAction::StaticClass());
	}
}


// Called every frame
void UActionLauncherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UActionLauncherComponent::ExecuteAction(ACharacterActor* actionLauncherCharacter, AHexCell* actionRecieverCell)
{
	if (myAction != NULL) {
		if (myAction->PerformAction(actionLauncherCharacter, actionRecieverCell)) {
			if (actionLauncherCharacter != nullptr && actionLauncherCharacter->GetActionsExecuted() >= actionLauncherCharacter->GetNumActions()) {
				ACombatGameMode* combatGameMode = Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());
				if (combatGameMode != nullptr) {
					combatGameMode->ContinueCombat();
				}
			}
		}
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("myAction is NULL"));
	}
	
	return true;
}

void UActionLauncherComponent::SetMyAction(UAction* newAction)
{
	myAction = newAction;
}
