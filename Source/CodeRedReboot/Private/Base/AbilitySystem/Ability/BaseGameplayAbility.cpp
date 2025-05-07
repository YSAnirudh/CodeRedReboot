// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/AbilitySystem/Ability/BaseGameplayAbility.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"

void UBaseGameplayAbility::PreActivate(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	OnGameplayAbilityEnded.AddUObject(this, &UBaseGameplayAbility::OnAbilityEnd);
}

UBaseAbilitySystemComponent* UBaseGameplayAbility::GetBaseAbilitySystemFromActorInfo() const
{
	return CurrentActorInfo ? Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent) : nullptr;
}

void UBaseGameplayAbility::OnAbilityEnd(UGameplayAbility* GameplayAbility)
{
	OnAbilityEndDelegate.Broadcast();
}
