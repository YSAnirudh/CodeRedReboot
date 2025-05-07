// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"
#include "BaseInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FBaseInputActionConfig {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<ETriggerEvent> EventsToTriggerInputOn;
};

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API UBaseInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UBaseInputConfig(const FObjectInitializer& Init);
	
	const TArray<FBaseInputActionConfig>& GetNativeInputActionConfigMap() const { return NativeInputActionMap; }
	const TArray<FBaseInputActionConfig>& GetAbilityInputActionConfigMap() const { return AbilityInputActionMap; }

	UFUNCTION(BlueprintCallable, Category = "Input")
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag, bool bLogIfNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "Input")
	UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogIfNotFound = true) const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<FBaseInputActionConfig> NativeInputActionMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<FBaseInputActionConfig> AbilityInputActionMap;
	
};
