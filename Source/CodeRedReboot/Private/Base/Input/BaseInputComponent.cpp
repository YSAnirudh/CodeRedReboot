// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Input/BaseInputComponent.h"

UBaseInputComponent::UBaseInputComponent(const FObjectInitializer& ObjectInitialzer)
{
}

void UBaseInputComponent::AddInputMappings(const UBaseInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	//if (InputSubsystem)
	//{
	//	// Native input actions.
	//	for (const FBaseInputActionConfig& InputActionConfig : InputConfig->GetNativeInputActionConfigMap())
	//	{
	//		for (ETriggerEvent TriggerEvent : InputActionConfig.EventsToTriggerInputOn)
	//		{
	//			InputActionConfig.InputTag.GetTagName().ToString().Replace('.', '_', ESearchCase::IgnoreCase);
	//		}
	//	}
	//}
}

void UBaseInputComponent::RemoveInputMappings(const UBaseInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
}

void UBaseInputComponent::RemoveAbilityBindings(TArray<uint32>& BindHandles)
{
	for (uint32& BindHandle : BindHandles)
	{
		RemoveBindingByHandle(BindHandle);
	}
	BindHandles.Reset();
}
