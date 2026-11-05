//Copyright Druid Mechanics;


#include "Character/AuraBaseCharacter.h"

// Sets default values
AAuraBaseCharacter::AAuraBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision );
	
}

UAbilitySystemComponent* AAuraBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraBaseCharacter::InitACInfo()
{
	
}


