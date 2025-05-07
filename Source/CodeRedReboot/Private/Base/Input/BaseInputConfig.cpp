// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Input/BaseInputConfig.h"
#include "BaseLogChannels.h"

UBaseInputConfig::UBaseInputConfig(const FObjectInitializer& Init)
{
}

UInputAction* UBaseInputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag, bool bLogIfNotFound) const
{
	for (const FBaseInputActionConfig& NInputAction : NativeInputActionMap)
	{
		if (NInputAction.InputAction != nullptr && NInputAction.InputTag == InputTag)
		{
			return NInputAction.InputAction;
		}
	}

	if (bLogIfNotFound)
	{
		UE_LOG(LogBaseInput, Warning, TEXT("Native Input Action with Tag {%s} not found!"), *InputTag.ToString());
	}

	return nullptr;
}

UInputAction* UBaseInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogIfNotFound) const
{
	for (const FBaseInputActionConfig& AInputAction : AbilityInputActionMap)
	{
		if (AInputAction.InputAction != nullptr && AInputAction.InputTag == InputTag)
		{
			return AInputAction.InputAction;
		}
	}

	if (bLogIfNotFound)
	{
		UE_LOG(LogBaseInput, Warning, TEXT("Ability Input Action with Tag {%s} not found!"), *InputTag.ToString());
	}

	return nullptr;
}