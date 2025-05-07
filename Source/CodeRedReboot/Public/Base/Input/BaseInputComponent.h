// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "BaseInputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "BaseInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API UBaseInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	UBaseInputComponent(const FObjectInitializer& ObjectInitialzer);

	void AddInputMappings(const UBaseInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const UBaseInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UBaseInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UBaseInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveAbilityBindings(TArray<uint32>& BindHandles);
};

template<class UserClass, typename FuncType>
inline void UBaseInputComponent::BindNativeAction(const UBaseInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* InpAction = InputConfig->FindNativeInputActionByTag(InputTag, bLogIfNotFound))
	{
		BindAction(InpAction, TriggerEvent, Object, Func);
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
inline void UBaseInputComponent::BindAbilityActions(const UBaseInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FBaseInputActionConfig& CRInputAction : InputConfig->GetAbilityInputActionConfigMap())
	{
		if (CRInputAction.InputAction != nullptr && CRInputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(CRInputAction.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, CRInputAction.InputTag).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(CRInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, CRInputAction.InputTag).GetHandle());
			}
		}
	}
}
