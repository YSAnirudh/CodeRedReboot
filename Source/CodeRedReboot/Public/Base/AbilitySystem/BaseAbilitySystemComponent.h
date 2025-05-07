// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Ability/BaseGameplayAbility.h"
#include "BaseAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AbilitySystem, hidecategories = (Object, LOD, Lighting, Transform, Sockets, TextureStreaming), editinlinenew, meta = (BlueprintSpawnableComponent))
class CODEREDREBOOT_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UBaseAbilitySystemComponent(const FObjectInitializer& Initializer);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

	/** Apply a gameplay effect to self */
	UFUNCTION(BlueprintCallable, Category = GameplayEffects, meta = (DisplayName = "ApplyGameplayEffectToSelfIfNotActive", ScriptName = "ApplyGameplayEffectToSelfIfNotActive"))
	FActiveGameplayEffectHandle BP_ApplyGameplayEffectToSelfIfNotActive(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext);
	FActiveGameplayEffectHandle ApplyGameplayEffectToSelfIfNotActive(const UGameplayEffect* GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, FPredictionKey PredictionKey = FPredictionKey());

	/** Activate an Ability By Tag */
	UFUNCTION(BlueprintCallable, Category = "CodeRed|GameplayAbility", meta = (DisplayName = "TryActivateAbilitiesByTag (First Active Ability)", ScriptName = "TryActivateAbilitiesByTag (First Active Ability)"))
	bool TryActivateAbilitiesByTag_Out_GA(const FGameplayTagContainer& Tags, UBaseGameplayAbility*& OutActivatedGameplayAbility, bool bAllowRemoteActivation = true);

	/** Activate an Ability By Class */
	UFUNCTION(BlueprintCallable, Category = "CodeRed|GameplayAbility", meta = (DisplayName = "TryActivateAbilitiesByClass (First Active Ability)", ScriptName = "TryActivateAbilitiesByClass (First Active Ability)"))
	bool TryActivateAbilitiesByClass_Out_GA(const TSubclassOf<UBaseGameplayAbility>& AbilityClass, UBaseGameplayAbility*& OutActivatedGameplayAbility, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category = "CodeRed|GameplayAbility")
	TArray<UBaseGameplayAbility*> GetActiveAbilitiesByTag(const FGameplayTagContainer& TagContainer, bool bMatchExact = true) const;
	TArray<UBaseGameplayAbility*> GetActiveAbilitiesByClass(const TSubclassOf<UBaseGameplayAbility>& AbilityClassToCheck) const;

	UFUNCTION(BlueprintCallable)
	void CancelAbilityWithTag(const FGameplayTag& InputTag);

	TArray<FGameplayAbilitySpecHandle> AbilityPressedHandles;
	TArray<FGameplayAbilitySpecHandle> AbilityReleasedHandles;
	TArray<FGameplayAbilitySpecHandle> AbilityHeldHandles;
	
	
};
