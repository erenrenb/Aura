// Copyright Druid Mechanics


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WC_Params)
{
	PlayerController = WC_Params.PlayerController;
	PlayerState= WC_Params.PlayerState;
	AbilitySystemComponent=WC_Params.AbilitySystemComponent;
	AttributeSet=WC_Params.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	
}
