#include "CharacterActor.h"
#include "Actions/Action.h"
#include "Cells/HexCell.h"

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
	
}

// Called every frame
void ACharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACharacterActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/////////////////////////////

void ACharacterActor::StartTurn_Implementation()
{
}

void ACharacterActor::RecieveDamage(int32 damageAmount) {
	currentHp -= (damageAmount - armor);
	if (currentHp <= 0) {
		Destroy();
	}
}

void ACharacterActor::RecieveMagicDamage(int32 damageAmount) {
	currentHp -= (damageAmount - magicArmor);
	if (currentHp <= 0) {
		Die();
	}
}

void ACharacterActor::RecieveHealing(int32 healAmount) {
	currentHp = FMath::Min<int32>(hp, currentHp + healAmount);
}

void ACharacterActor::Block() {

	armor += armor / 2;
}

void ACharacterActor::Die() {

	Destroy();
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
AHexCell* ACharacterActor::GetMyCell()
{
	return myCell;
}
void ACharacterActor::SetCharacterCell(AHexCell* myNewCell) {
	myCell = myNewCell;
	SetActorLocation(myCell->GetActorLocation());
}
