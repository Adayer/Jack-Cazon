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
	armor = 3;
	damage = 5;
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
	hp -= (damageAmount - armor);
	if (hp <= 0) {
		Destroy();
	}
}

int32 ACharacterActor::GetAttackPower() {
	return damage;
}

float ACharacterActor::GetAttackRange() {
	return attackRange;
}
