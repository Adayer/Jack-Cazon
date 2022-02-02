#include "CharacterActor.h"
#include "Actions/Action.h"
#include "Cells/HexCell.h"
#include "Actions/AtomicActions/ModifyArmorAtomicAction.h"

// Sets default values
ACharacterActor::ACharacterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterActor::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void ACharacterActor::RecieveDamage(int32 damageAmount) {
	currentHp -= (damageAmount - armor);
	if (currentHp <= 0) {
		Die();
		
	}
}

void ACharacterActor::RecieveMagicDamage(int32 damageAmount) {
	currentHp -= (damageAmount - magicArmor);
	if (currentHp <= 0) {
		Die();
	}
}

void ACharacterActor::RecieveDirectDamage(int32 damageAmount)
{
	currentHp -= damageAmount;
	if (currentHp <= 0) {
		Die();
	}
}

void ACharacterActor::RecieveHealing(int32 healAmount) {
	currentHp = FMath::Min<int32>(hp, currentHp + healAmount);
}

void ACharacterActor::Block() {

	int armorUpgrade = armor / 2;
	ModifyArmor(armorUpgrade);
	UModifyArmorAtomicAction* armorReduction = NewObject<UModifyArmorAtomicAction>();
	armorReduction->armorVariation = -armorUpgrade;
	AddStartingTurnAction(armorReduction, 1);
}

void ACharacterActor::ModifyArmor(int armorVariation) {
	armor += armorVariation;
}

void ACharacterActor::Die() {
	SetActorHiddenInGame(true);
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
