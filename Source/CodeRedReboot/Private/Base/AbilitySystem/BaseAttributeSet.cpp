// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/AbilitySystem/BaseAttributeSet.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "BaseLogChannels.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	APawn* TargetPawn = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetPawn = Cast<APawn>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		UE_LOG(LogBaseAbilitySystem, Verbose, TEXT("Health changed to: %f"), GetHealth());

		if (GetHealth() <= 0.0f)
		{
			UE_LOG(LogBaseAbilitySystem, Log, TEXT("Character Died!"));
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		SetMaxHealth(FMath::Max(GetMaxHealth(), 0.0f));

		if (GetHealth() > GetMaxHealth())
		{
			SetHealth(GetMaxHealth());
		}
	}
}
