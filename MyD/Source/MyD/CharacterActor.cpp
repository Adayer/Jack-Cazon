#include "CharacterActor.h"
#include "Actions/Action.h"
#include "Cells/HexCell.h"
#include "Actions/AtomicActions/ModifyArmorAtomicAction.h"
#include <MyD/Actions/AtomicActions/ShowPlayerInfoTextAtomicAction.h>
#include <MyD/Actions/AtomicActions/HidePlayerInfoTextAtomicAction.h>
#include "TurnSystem/CombatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include <MyD/Actions/AtomicActions/RemoveStunAtomicAction.h>
#include "SavedPlayerData.h"

// Sets default values
ACharacterActor::ACharacterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	infoTextRender = CreateDefaultSubobject<UTextRenderComponent>("infoTextRender");
	infoTextRender->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacterActor::BeginPlay()
{
	Super::BeginPlay();

	infoTextRender->SetTextRenderColor(FColor::Red);
	HideInfoText();
	
	///////// TEMP
	hp = 10;
	currentHp = hp;
	armor = 1;
	magicArmor = 2;
	damage = 15;
	magicDamage = 5;
	attackRange = 2;
	movement = 5;

	numActions = 2;
	actionsExecuted = 0;

	/////// Puede ser k diesen erro si se hacen los new en el constructor
	startTurnActions = NewObject<UActionsQueue>();
	tickActions = NewObject<UActionsQueue>();
}

// Called every frame
void ACharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tickActions->UpdateTimeUnits(DeltaTime);

	TArray<UAtomicAction*> turnActions = tickActions->Pop();

	for (UAtomicAction* action : turnActions) {
		action->ExecuteAtomicAction(this);
	}
}
void ACharacterActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/////////////////////////////

void ACharacterActor::StartTurn_Implementation()
{
	startTurnActions->UpdateTimeUnits(1.f);
	TArray<UAtomicAction*> turnActions = startTurnActions->Pop();

	for (UAtomicAction* action : turnActions){
		action->ExecuteAtomicAction(this);
	}

	UE_LOG(LogTemp, Warning, TEXT("Start turn"));

	actionsExecuted = 0;

	if (stunned) {
		actionsExecuted = numActions;

		ShowTextInInfoText(FText::FromString(FString("Stunned")));
	}
}

void ACharacterActor::RecieveDamage(int32 damageAmount) {
	int damageRecieved = damageAmount - armor;

	ShowDamageRecievedText(damageRecieved);

	currentHp -= damageRecieved;
	if (currentHp <= 0) {
		Die();
		
	}
}

void ACharacterActor::RecieveMagicDamage(int32 damageAmount) {
	int damageRecieved = damageAmount - magicArmor;
	currentHp -= damageRecieved;

	ShowDamageRecievedText(damageRecieved);

	if (currentHp <= 0) {
		Die();
	}
}

void ACharacterActor::RecieveDirectDamage(int32 damageAmount)
{
	ShowDamageRecievedText(damageAmount);

	currentHp -= damageAmount;
	if (currentHp <= 0) {
		Die();
	}
}

void ACharacterActor::RecieveHealing(int32 healAmount) {
	int previousCurrentHP = currentHp;
	currentHp = FMath::Min<int32>(hp, currentHp + healAmount);

	ShowHealingRecievedText(currentHp - previousCurrentHP);
}

void ACharacterActor::Block() {

	int armorUpgrade = armor / 2;
	ModifyArmor(armorUpgrade);
	UModifyArmorAtomicAction* armorReduction = NewObject<UModifyArmorAtomicAction>();
	armorReduction->armorVariation = -armorUpgrade;
	AddStartingTurnAction(armorReduction, 1);

	ShowTextInInfoText(FText::FromString(FString("Block")));
}

void ACharacterActor::ModifyArmor(int armorVariation) {
	armor += armorVariation;
}

void ACharacterActor::Modifyattack(int attackVariation)
{
	damage += attackVariation;
}

void ACharacterActor::GetStunned(int numberOfTurnsStuned)
{
	stunned = true;

	URemoveStunAtomicAction* removeStunAtomicAction = NewObject<URemoveStunAtomicAction>();
	AddStartingTurnAction(removeStunAtomicAction, numberOfTurnsStuned);

	ShowTextInInfoText(FText::FromString(FString("Stunned: ").Append(FString::FromInt(numberOfTurnsStuned))));
}

void ACharacterActor::RemoveStun()
{
	stunned = false;
}

void ACharacterActor::Die() {
	startTurnActions->Empty();
	tickActions->Empty();

	myCell->SetCharacterInCell(nullptr);
	SetActorHiddenInGame(true);
	ACombatGameMode* CombatGM = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CombatGM->CharacterHasDied();
}

void ACharacterActor::ShowInfoText(FText newInfoText)
{
	UpdateInfoText(newInfoText);
}

void ACharacterActor::UpdateInfoText(FText newInfoText)
{
	infoTextRender->SetText(newInfoText);
}

void ACharacterActor::HideInfoText()
{
	UpdateInfoText(FText::GetEmpty());
}

void ACharacterActor::ShowTextInInfoText(FText newInfoText, FColor textColor)
{
	infoTextRender->TextRenderColor = textColor;

	UShowPlayerInfoTextAtomicAction* showPlayerInfoTextAtomicAction = NewObject<UShowPlayerInfoTextAtomicAction>();
	showPlayerInfoTextAtomicAction->textToShow = newInfoText;

	AddTickAction(showPlayerInfoTextAtomicAction, 0.f);
	AddTickAction(NewObject<UHidePlayerInfoTextAtomicAction>(), 1.f);
}

void ACharacterActor::ShowDamageRecievedText(int damageRecieved)
{
	ShowTextInInfoText(FText::FromString(FString("-").Append(FString::FromInt(damageRecieved))));
}

void ACharacterActor::ShowHealingRecievedText(int healingRecieved)
{
	ShowTextInInfoText(FText::FromString(FString("+").Append(FString::FromInt(healingRecieved))));
}

void ACharacterActor::AddStartingTurnAction(UAtomicAction* startingTurnAction, int turnsLeftToExecuteAction)
{
	startTurnActions->Push(startingTurnAction, float(turnsLeftToExecuteAction));
}

void ACharacterActor::AddStartingTurnActionRepeatable(UAtomicAction* startingTurnAction, int numTurnsExecutingAction)
{
	for (int i = 1; i <= numTurnsExecutingAction; ++i) {
		AddStartingTurnAction(startingTurnAction, i);
	}
}

void ACharacterActor::AddTickAction(UAtomicAction* startingTurnAction, float secondsToExecuteAction)
{
	tickActions->Push(startingTurnAction, secondsToExecuteAction);
}

int ACharacterActor::GetNumActions()
{
	return numActions;
}

int ACharacterActor::GetActionsExecuted()
{
	return actionsExecuted;
}

void ACharacterActor::IncreaseActionsExecuted()
{
	++actionsExecuted;
}

int32 ACharacterActor::GetAttackPower() {
	return damage;
}

int32 ACharacterActor::GetMagicAttackPower() {
	return magicDamage;
}

int ACharacterActor::GetAttackRange() {
	return attackRange;
}

int ACharacterActor::GetMovementRange() {
	return movement;
}

AHexCell* ACharacterActor::GetMyCell()
{
	return myCell;
}

void ACharacterActor::SetCharacterCell(AHexCell* myNewCell) {
	myCell = myNewCell;
	SetActorLocation(myCell->GetActorLocation());
}

void ACharacterActor::SetStats(USavedPlayerData* _data)
{
	hp = _data->hp;
	armor = _data->armor;
	damage = _data->damage;
	magicArmor = _data->magicArmor;
	magicDamage = _data->magicDamage;
	playerRol = _data->playerRol;

	skill1 = Cast<UAction>(_data->skill1->GetDefaultObject());
	skill2 = Cast<UAction>(_data->skill2->GetDefaultObject());
	block = Cast<UAction>(_data->block->GetDefaultObject());
};

