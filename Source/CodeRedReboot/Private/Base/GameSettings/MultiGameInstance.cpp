// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameSettings/MultiGameInstance.h"
#include "BaseLogChannels.h"
#include "Kismet/GameplayStatics.h"
#include "Base/Levels/LevelManagerSubsystem.h"

UMultiGameInstance::UMultiGameInstance()
{
}

void UMultiGameInstance::Init()
{
	Super::Init();

	if (GameInformationTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Info Table"))

		TArray<FGameInformation*> GameInfoRawTable;
		GameInformationTable->GetAllRows<FGameInformation>(TEXT("Game Information Table"), GameInfoRawTable);

		GameInformationList.Empty();
		for (const FGameInformation* GameInfo : GameInfoRawTable)
		{
			GameInformationList.Add(*GameInfo);
		}
	}

	UE_LOG(LogMultiGameInstance, Log, TEXT("MultiGameInstance Initialized"));
}

void UMultiGameInstance::SwitchGame(EGameType NewGameType)
{
	if (CurrentGameType != NewGameType || (CurrentGameType != EGameType::Hub && NewGameType != EGameType::Hub))
	{
		// Notify listeners about the game type change
		OnGameTypeChanged.Broadcast(CurrentGameType, NewGameType);

		TArray<FPrimaryAssetId> LevelAssetIds = GetGameLevelAssetIds(NewGameType);

		if (!LevelAssetIds.IsEmpty())
		{

			/*FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "OnLevelLoadComplete";
			LatentInfo.UUID = FGuid::NewGuid().A;
			LatentInfo.Linkage = 0;*/

			ULevelManagerSubsystem* LevelManagerSubsystem = GetSubsystem<ULevelManagerSubsystem>();
			if (LevelManagerSubsystem)
			{
				LevelManagerSubsystem->LoadGameLevels(LevelAssetIds);
			}

			UE_LOG(LogMultiGameInstance, Log, TEXT("Switching to game: %s"), *UEnum::GetValueAsString(CurrentGameType));
		}
		else
		{
			UE_LOG(LogMultiGameInstance, Warning, TEXT("No level path found for game type: %s"), *UEnum::GetValueAsString(CurrentGameType));
		}
	}
}

TArray<FPrimaryAssetId> UMultiGameInstance::GetGameLevelAssetIds(EGameType GameType) const
{
	for (const FGameInformation& GameInfo : GameInformationList)
	{
		if (GameInfo.GameType == GameType)
		{
			TArray<FPrimaryAssetId> LevelAssetIds;
			for (const auto& LevelMapEntry : GameInfo.LevelDataMap)
			{
				LevelAssetIds.Add(LevelMapEntry.Value);
			}
			return LevelAssetIds;
		}
	}

	return TArray<FPrimaryAssetId>();
}

void UMultiGameInstance::OnLevelStreamingComplete()
{
	CurrentGameLoadProgress = 1.0f;
	OnGameLoadComplete.Broadcast(CurrentGameType);
	UE_LOG(LogMultiGameInstance, Log, TEXT("Level streaming complete for game type: %s"), *UEnum::GetValueAsString(CurrentGameType));
}

void UMultiGameInstance::SaveGameState()
{
	UE_LOG(LogMultiGameInstance, Log, TEXT("Saving game state for game type (Place holder): %s"), *UEnum::GetValueAsString(CurrentGameType));
}

void UMultiGameInstance::LoadGameState()
{
	UE_LOG(LogMultiGameInstance, Log, TEXT("Loding game state for game type (Place holder): %s"), *UEnum::GetValueAsString(CurrentGameType));
}
