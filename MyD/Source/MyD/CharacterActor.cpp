#include "CharacterActor.h"

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
	
	///////// TEMP
	hp = 10;
	currentHp = hp;
	armor = 3;
	magicArmor = 2;
	damage = 5;
	magicDamage = 5;
	attackRange = 2;
}

// Called every frame
void ACharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/////////////////////////////

void ACharacterActor::StartTurn_Implementation()
{
}

void ACharacterActor::RecieveDamage(int32 damageAmount) {
	currentHp -= (damageAmount - armor);
	if (hp <= 0) {
		Destroy();
	}
}

void ACharacterActor::RecieveMagicDamage(int32 damageAmount) {
	currentHp -= (damageAmount - magicArmor);
	if (currentHp <= 0) {
		Destroy();
	}
}

void ACharacterActor::RecieveHealing(int32 healAmount) {
	currentHp = FMath::Min<int32>(hp, currentHp + healAmount);
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
