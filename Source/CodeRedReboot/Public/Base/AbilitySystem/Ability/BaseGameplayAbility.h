// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	AAP_None				UMETA(DisplayName = "None"),
	AAP_OnInputTriggered	UMETA(DisplayName = "OnInputTriggered"),
	AAP_WhileInputActive	UMETA(DisplayName = "WhileInputActive"),
	AAP_OnSpawned			UMETA(DisplayName = "OnSpawned"),
	AAP_MAX					UMETA(Hidden),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnd);

class UBaseAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CodeRed|Ability", meta = (AllowPrivateAccess = "true"))
	EAbilityActivationPolicy AbilityActivationPolicy;

protected:

	virtual void PreActivate(
		FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate,
		const FGameplayEventData* TriggerEventData
	) override;

public:

	FORCEINLINE EAbilityActivationPolicy GetActivationPolicy() const { return AbilityActivationPolicy; }

	UFUNCTION(BlueprintCallable, Category = "CodeRed|Ability")
	UBaseAbilitySystemComponent* GetBaseAbilitySystemFromActorInfo() const;

public:

	UFUNCTION()
	void OnAbilityEnd(UGameplayAbility* GameplayAbility);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityEndDelegate;
};
