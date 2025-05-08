// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameType : uint8
{
	Hub	UMETA(DisplayName = "Hub"),
	GOW	UMETA(DisplayName = "GOW"),
	SpiderMan	UMETA(DisplayName = "SpiderMan"),
	Control UMETA(DisplayName = "Control"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameTypeChanged, EGameType, PreviousGameType, EGameType, NewGameType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameLoadComplete, EGameType, LoadedGameType);

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API UMultiGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UMultiGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	void SwitchGame(EGameType NewGameType);

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	EGameType GetCurrentGameType() const { return CurrentGameType; }

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	FString GetGameLevelPath(EGameType GameType) const;

	float GetCurrentGameLoadingProgress() const { return CurrentGameLoadProgress; }

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	void SaveGameState();

	UFUNCTION(BlueprintCallable, Category = "Game Switching")
	void LoadGameState();
	
	UPROPERTY(BlueprintAssignable, Category = "Game Switching")
	FOnGameTypeChanged OnGameTypeChanged;

	UPROPERTY(BlueprintAssignable, Category = "Game Switching")
	FOnGameLoadComplete OnGameLoadComplete;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Game Switching")
	EGameType CurrentGameType;

	UPROPERTY(EditDefaultsOnly, Category = "Game Switching")
	TMap<EGameType, FString> GameLevelPaths;

	void InitializeDefaultLevelPaths();

private:

	float CurrentGameLoadProgress = 0.0f;

	void OnLevelStreamingComplete();
	
};
