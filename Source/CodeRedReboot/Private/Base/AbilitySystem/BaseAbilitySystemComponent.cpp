// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "Base/AbilitySystem/Ability/BaseGameplayAbility.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayAbilitySpec.h"

UBaseAbilitySystemComponent::UBaseAbilitySystemComponent(const FObjectInitializer& Initializer)
{
	AbilityPressedHandles.Reset();
	AbilityReleasedHandles.Reset();
	AbilityHeldHandles.Reset();
}

void UBaseAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)))
			{
				AbilityPressedHandles.AddUnique(AbilitySpec.Handle);
				AbilityHeldHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UBaseAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)))
			{
				AbilityReleasedHandles.AddUnique(AbilitySpec.Handle);
				AbilityHeldHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UBaseAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	if (HasMatchingGameplayTag(BaseGameplayTags::Gameplay_AbilityInputBlocked))
	{
		ClearAbilityInput();
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilityPressedHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability)
			{
				Spec->InputPressed = true;

				if (Spec->IsActive())
				{
					//UE_LOG(LogCodeRed, Warning, TEXT("Ability Input Pressed with Handle: %s"), *SpecHandle.ToString());
					AbilitySpecInputPressed(*Spec);
				}
				else
				{
					const UBaseGameplayAbility* CRAbility = CastChecked<UBaseGameplayAbility>(Spec->Ability);
					if (CRAbility->GetActivationPolicy() == EAbilityActivationPolicy::AAP_OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(Spec->Handle);
					}
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilityHeldHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && !Spec->IsActive())
			{
				const UBaseGameplayAbility* CRAbility = CastChecked<UBaseGameplayAbility>(Spec->Ability);

				if (CRAbility->GetActivationPolicy() == EAbilityActivationPolicy::AAP_WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(Spec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilitiesToActivate)
	{
		UE_LOG(LogBaseAbilitySystem, Warning, TEXT("Trying to Activate Ability with Handle: %s"), *SpecHandle.ToString());
		TryActivateAbility(SpecHandle);
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilityReleasedHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability)
			{
				Spec->InputPressed = false;

				if (Spec->IsActive())
				{
					//UE_LOG(LogCodeRed, Warning, TEXT("Ability Input Released with Handle: %s"), *SpecHandle.ToString());
					AbilitySpecInputReleased(*Spec);
				}
			}
		}
	}

	AbilityPressedHandles.Reset();
	AbilityReleasedHandles.Reset();
}

void UBaseAbilitySystemComponent::ClearAbilityInput()
{
	AbilityPressedHandles.Reset();
	AbilityReleasedHandles.Reset();
	AbilityHeldHandles.Reset();
}

void UBaseAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputRelease ability task works.
	if (Spec.IsActive())
	{
		// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, FPredictionKey());
	}
}

void UBaseAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputRelease ability task works.
	if (Spec.IsActive())
	{
		// Invoke the InputReleased event. This is not replicated here. If someone is listening, they may replicate the InputReleased event to the server.
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, FPredictionKey());
	}
}

TArray<FGameplayAbilitySpecHandle> UBaseAbilitySystemComponent::GetAbilitySpecHandlesByInputTag(const FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpecHandle> Results;

	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				Results.Add(AbilitySpec.Handle);
			}
		}
	}

	return Results;
}

bool UBaseAbilitySystemComponent::HasActiveAbilityWithTag(const FGameplayTag& AbilityTag)
{
	if (!AbilityTag.IsValid())
	{
		return false;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && AbilitySpec.IsActive())
		{
			if (AbilitySpec.Ability->GetAssetTags().HasTag(AbilityTag))
			{
				return true;
			}
		}
	}

	return false;
}

FActiveGameplayEffectHandle UBaseAbilitySystemComponent::BP_ApplyGameplayEffectToSelfIfNotActive(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext)
{
	if (GameplayEffectClass)
	{
		if (!EffectContext.IsValid())
		{
			EffectContext = MakeEffectContext();
		}

		UGameplayEffect* GameplayEffect = GameplayEffectClass->GetDefaultObject<UGameplayEffect>();
		return ApplyGameplayEffectToSelfIfNotActive(GameplayEffect, Level, EffectContext);
	}

	return FActiveGameplayEffectHandle();
}

FActiveGameplayEffectHandle UBaseAbilitySystemComponent::ApplyGameplayEffectToSelfIfNotActive(const UGameplayEffect* GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, FPredictionKey PredictionKey)
{
	if (GameplayEffect == nullptr)
	{
		UE_LOG(LogAbilitySystemComponent, Error, TEXT("UAbilitySystemComponent::ApplyGameplayEffectToSelfIfNotActive called by Instigator %s with a null GameplayEffect."), *EffectContext.ToString());
		return FActiveGameplayEffectHandle();
	}

	if (HasNetworkAuthorityToApplyGameplayEffect(PredictionKey))
	{
		// Query with Gameplay Effect class
		FGameplayEffectQuery GEQuery;
		GEQuery.EffectDefinition = GameplayEffect->GetClass();

		// Get Active Effects with the query.
		TArray<FActiveGameplayEffectHandle> ActiveEffects = GetActiveEffects(GEQuery);
		if (ActiveEffects.Num() > 0)
		{
			// If theres atleast one, it means the effect is active.
			return FActiveGameplayEffectHandle();
		}

		FGameplayEffectSpec	Spec(GameplayEffect, EffectContext, Level);
		return ApplyGameplayEffectSpecToSelf(Spec, PredictionKey);
	}

	return FActiveGameplayEffectHandle();
}

bool UBaseAbilitySystemComponent::TryActivateAbilitiesByTag_Out_GA(const FGameplayTagContainer& Tags, UBaseGameplayAbility*& OutActivatedGameplayAbility, bool bAllowRemoteActivation)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivatePtrs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tags, AbilitiesToActivatePtrs);
	if (AbilitiesToActivatePtrs.Num() == 0)
	{
		return false;
	}

	// Convert from pointers (which can be reallocated, since they point to internal data) to copies of that data
	TArray<FGameplayAbilitySpec> AbilitiesToActivate;
	AbilitiesToActivate.Reserve(AbilitiesToActivatePtrs.Num());
	Algo::Transform(AbilitiesToActivatePtrs, AbilitiesToActivate, [](FGameplayAbilitySpec* SpecPtr) { return *SpecPtr; });

	bool bSuccess = false;
	for (const FGameplayAbilitySpec& GameplayAbilitySpec : AbilitiesToActivate)
	{
		ensure(IsValid(GameplayAbilitySpec.Ability));
		bSuccess |= TryActivateAbility(GameplayAbilitySpec.Handle, bAllowRemoteActivation);
	}

	TArray<UBaseGameplayAbility*> ActiveAbilities = GetActiveAbilitiesByTag(Tags);

	if (bSuccess && ActiveAbilities.Num() > 0)
	{
		OutActivatedGameplayAbility = ActiveAbilities[0];
	}

	return bSuccess;
}

bool UBaseAbilitySystemComponent::TryActivateAbilitiesByClass_Out_GA(const TSubclassOf<UBaseGameplayAbility>& AbilityClass, UBaseGameplayAbility*& OutActivatedGameplayAbility, bool bAllowRemoteActivation)
{
	bool bSuccess = false;

	const UGameplayAbility* const InAbilityCDO = AbilityClass.GetDefaultObject();

	for (const FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.Ability == InAbilityCDO)
		{
			bSuccess |= TryActivateAbility(Spec.Handle, bAllowRemoteActivation);
			break;
		}
	}

	TArray<UBaseGameplayAbility*> ActiveAbilities = GetActiveAbilitiesByClass(AbilityClass);

	if (bSuccess && ActiveAbilities.Num() > 0)
	{
		OutActivatedGameplayAbility = ActiveAbilities[0];
	}

	return bSuccess;
}

TArray<UBaseGameplayAbility*> UBaseAbilitySystemComponent::GetActiveAbilitiesByTag(const FGameplayTagContainer& TagContainer, bool bMatchExact) const
{
	TArray<UBaseGameplayAbility*> ActiveAbilities;

	const TArray<FGameplayAbilitySpec>& TempActivatableAbilities = GetActivatableAbilities();
	TArray<const FGameplayAbilitySpec*> MatchingAbilitySpecs;

	for (const FGameplayAbilitySpec& Spec : TempActivatableAbilities)
	{
		if (Spec.Ability)
		{
			const bool bMatched = bMatchExact ? Spec.Ability->GetAssetTags().HasAllExact(TagContainer) : Spec.Ability->GetAssetTags().HasAll(TagContainer);
			if (bMatched)
			{
				TArray<UGameplayAbility*> AbilityInstances = Spec.GetAbilityInstances();
				for (UGameplayAbility* AbilityInstance : AbilityInstances)
				{
					UBaseGameplayAbility* CRAbility = Cast<UBaseGameplayAbility>(AbilityInstance);
					if (CRAbility && CRAbility->IsActive())
					{
						ActiveAbilities.AddUnique(CRAbility);
					}
				}
			}
		}
	}

	return ActiveAbilities;
}

TArray<UBaseGameplayAbility*> UBaseAbilitySystemComponent::GetActiveAbilitiesByClass(const TSubclassOf<UBaseGameplayAbility>& AbilityClassToCheck) const
{
	TArray<UBaseGameplayAbility*> ActiveAbilities;

	const TArray<FGameplayAbilitySpec>& TempActivatableAbilities = GetActivatableAbilities();
	TArray<const FGameplayAbilitySpec*> MatchingAbilitySpecs;

	for (const FGameplayAbilitySpec& Spec : TempActivatableAbilities)
	{
		if (Spec.Ability && Spec.Ability->GetClass()->IsChildOf(AbilityClassToCheck))
		{
			TArray<UGameplayAbility*> AbilityInstances = Spec.GetAbilityInstances();
			for (UGameplayAbility* AbilityInstance : AbilityInstances)
			{
				UBaseGameplayAbility* CRAbility = Cast<UBaseGameplayAbility>(AbilityInstance);
				if (CRAbility->IsActive())
				{
					ActiveAbilities.AddUnique(CRAbility);
				}
			}
		}
	}

	return ActiveAbilities;
}

void UBaseAbilitySystemComponent::CancelAbilityWithTag(const FGameplayTag& InputTag)
{
	FGameplayTagContainer Tags(InputTag);
	CancelAbilities(&Tags);
}
