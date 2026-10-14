// Copyright Druid Mechanics


#include "HUD/AuraHUD.h"

#include "Dataflow/DataflowOverlay.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WC_Params)
{
	
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WC_Params);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	OverlayWidget=CreateWidget<UAuraUserWidget>(GetWorld(),OverlayWidgetClass);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidget->AddToViewport();
}

