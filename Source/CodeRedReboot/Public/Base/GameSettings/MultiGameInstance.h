// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Base/Data/GameInformationStructs.h"
#include "MultiGameInstance.generated.h"

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
	TArray<FPrimaryAssetId> GetGameLevelAssetIds(EGameType GameType) const;

	UFUNCTION(BlueprintCallable, Category = "Game Information")
	const TArray<FGameInformation>& GetGameInformationList() const { return GameInformationList; };

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

	TArray<FGameInformation> GameInformationList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Game Switching")
	UDataTable* GameInformationTable;

private:

	float CurrentGameLoadProgress = 0.0f;

	void OnLevelStreamingComplete();
	
};
