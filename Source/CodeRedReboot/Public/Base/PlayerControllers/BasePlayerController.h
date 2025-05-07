// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "BasePlayerController.generated.h"

class UBaseInputConfig;
class UBaseAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ABasePlayerController();
	
protected:

	virtual void SetupInputComponent() override;

	void Input_AbilityInputTagPressed(FGameplayTag AbilityInputTag);
	void Input_AbilityInputTagReleased(FGameplayTag AbilityInputTag);

protected:

	virtual void PostProcessInput(float DeltaTime, bool bGamePaused) override;

protected:

	// TEMP INPUT MAPPING
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	const UBaseInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext = nullptr;
};
