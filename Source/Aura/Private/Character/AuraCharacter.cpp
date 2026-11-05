// Copyright Druid Mechanics


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Ability/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "State/Aura_PlayerState.h"
#include "Input/AuraPlayerController.h"
#include "HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	// 角色移动方向决定角色朝向
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 角色旋转速度
	GetCharacterMovement()->RotationRate =
		FRotator(0.f, 400.f, 0.f);

	// 限制角色只能在平面移动
	GetCharacterMovement()->bConstrainToPlane = true;

	// 生成时把角色位置吸附到移动平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	// 不使用Controller控制Pitch旋转
	bUseControllerRotationPitch = false;

	// 不使用Controller控制Roll旋转
	bUseControllerRotationRoll = false;

	// 不使用Controller控制Yaw旋转
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//init ability actor info for server
	InitACInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for client
	InitACInfo();
}

void AAuraCharacter::InitACInfo()
{
	AAura_PlayerState* Aura_PlayerState=GetPlayerState<AAura_PlayerState>();
	check(Aura_PlayerState);
	Aura_PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(Aura_PlayerState,this);
	Cast<UAuraAbilitySystemComponent>(Aura_PlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent=Aura_PlayerState->GetAbilitySystemComponent();
	AttributeSet=Aura_PlayerState->GetAttributeSet();
	
	// ↓ 新增：初始化 HUD 并注入 WidgetController
	if (AAuraPlayerController* AuraPC = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPC->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPC, Aura_PlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
