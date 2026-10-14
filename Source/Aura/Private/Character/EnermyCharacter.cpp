// Copyright Druid Mechanics


#include "Character/EnermyCharacter.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Ability/AuraAttributeSet.h"
#include "Aura/Aura.h"

AEnermyCharacter::AEnermyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}

void AEnermyCharacter::HighLightActor()
{
	// 敌人被高亮时（如鼠标悬停/选中）执行的逻辑，例如开启描边
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnermyCharacter::UnHighLightActor()
{
	// 敌人取消高亮时执行的逻辑，例如关闭描边
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnermyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

