// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
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

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowLoadingScreen();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideLoadingScreen();
	
protected:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void Input_AbilityInputTagPressed(FGameplayTag AbilityInputTag);
	void Input_AbilityInputTagReleased(FGameplayTag AbilityInputTag);

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	void SwitchGame(EGameType NewGameType);

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	void ReturnToHub();

	UFUNCTION()
	void OnGameTypeChanged(EGameType PreviousGameType, EGameType NewGameType);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LoadingScreenClass;

	UPROPERTY()
	UUserWidget* LoadingScreenWidget = nullptr;

	UFUNCTION()
	void OnLevelLoadComplete();

	UFUNCTION()
	void UpdateInputMappingContext(EGameType GameType);

	virtual void PostProcessInput(float DeltaTime, bool bGamePaused) override;

protected:

	// TEMP INPUT MAPPING
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UBaseInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<EGameType, UInputMappingContext*> GameInputMappingContexts;
};
