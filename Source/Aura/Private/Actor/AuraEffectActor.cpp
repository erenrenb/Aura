// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Ability/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootSceneComponent"));
	/*  Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());  */
}

/*
void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttribute=Cast<UAuraAttributeSet>
		(ASCInterface->GetAbilitySystemComponent()
			->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAuraAttribute=const_cast<UAuraAttributeSet*>(AuraAttribute);
		MutableAuraAttribute->SetHealth(MutableAuraAttribute->GetHealth()+25.0f);
		Destroy();
	}	
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
*/

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	/*  Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlap);  */
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	if (!GameplayEffectClass)
	{
		// 不要用 check()：某个实例/蓝图漏配 GameplayEffectClass 时会直接把编辑器崩掉
		UE_LOG(LogTemp, Warning, TEXT("[Aura] %s: ApplyEffectToTarget got null GameplayEffectClass (target=%s), skipped"),
			*GetName(), *GetNameSafe(TargetActor));
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	//Data.Get()获取普通指针
	/*	
	表达式	                          C++ 类型
	EffectSpecHandle	              FGameplayEffectSpecHandle
	EffectSpecHandle.Data	          TSharedPtr<FGameplayEffectSpec>
	EffectSpecHandle.Data.Get()	      FGameplayEffectSpec*
	*EffectSpecHandle.Data.Get()	  FGameplayEffectSpec&（表达式是左值，可绑定到 const FGameplayEffectSpec&） */
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

