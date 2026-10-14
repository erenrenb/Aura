// Copyright Druid Mechanics


#include "Input/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Interface/LightingInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CurserTrace();
}

void AAuraPlayerController::CurserTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	LastActor = ThisActor;
	ThisActor = nullptr;

	AActor* HitActor = CursorHit.GetActor();
	if (CursorHit.bBlockingHit && IsValid(HitActor) && HitActor->Implements<ULightingInterface>())
	{
		ThisActor = Cast<ILightingInterface>(HitActor);
	}

	if (LastActor == ThisActor)
	{
		return;
	}

	if (LastActor)
	{
		LastActor->UnHighLightActor();
	}

	if (ThisActor)
	{
		ThisActor->HighLightActor();
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);
	
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComp =CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	
		// 获取输入轴的二维向量
		const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

		// 获取当前控制器旋转
		const FRotator Rotation = GetControlRotation();

		// 只保留Yaw（水平旋转），去掉Pitch和Roll
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);


		// 根据Yaw旋转计算角色前方向
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// 根据Yaw旋转计算角色右方向
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


		// 获取当前控制的Pawn
		if (APawn* ControlledPawn = GetPawn<APawn>())
		{
			// Y轴控制前后移动
			ControlledPawn->AddMovementInput(
				ForwardDirection,
				InputAxisVector.Y
			);

			// X轴控制左右移动
			ControlledPawn->AddMovementInput(
				RightDirection,
				InputAxisVector.X
			);
		}
	
}


