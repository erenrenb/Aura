// Copyright Druid Mechanics


#include "State/Aura_PlayerState.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Ability/AuraAttributeSet.h"

AAura_PlayerState::AAura_PlayerState()
{
	SetNetUpdateFrequency(100.0f);
	
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAura_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
