// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameSettings/MultiGameInstance.h"
#include "BaseLogChannels.h"
#include "Kismet/GameplayStatics.h"

UMultiGameInstance::UMultiGameInstance()
{
	CurrentGameType = EGameType::Hub;
}

void UMultiGameInstance::Init()
{
	Super::Init();
	// Initialize default level paths
	InitializeDefaultLevelPaths();

	UE_LOG(LogMultiGameInstance, Log, TEXT("MultiGameInstance Initialized"));
}

void UMultiGameInstance::SwitchGame(EGameType NewGameType)
{
	if (CurrentGameType != NewGameType || (CurrentGameType != EGameType::Hub && NewGameType != EGameType::Hub))
	{
		// Notify listeners about the game type change
		OnGameTypeChanged.Broadcast(CurrentGameType, NewGameType);

		FString LevelPath = GetGameLevelPath(CurrentGameType);

		if (!LevelPath.IsEmpty())
		{
			UGameplayStatics::OpenLevel(this, FName(*LevelPath));
			UE_LOG(LogMultiGameInstance, Log, TEXT("Switching to game: %s"), *UEnum::GetValueAsString(CurrentGameType));
		}
		else
		{
			UE_LOG(LogMultiGameInstance, Warning, TEXT("No level path found for game type: %s"), *UEnum::GetValueAsString(CurrentGameType));
		}
	}
}

FString UMultiGameInstance::GetGameLevelPath(EGameType GameType) const
{
	if (GameLevelPaths.Contains(GameType))
	{
		return GameLevelPaths[GameType];
	}

	return TEXT("/Game/Hub/Levels/L_Hub");
}

void UMultiGameInstance::InitializeDefaultLevelPaths()
{
	GameLevelPaths.Add(EGameType::Hub, TEXT("/Game/Hub/Levels/L_Hub"));
	GameLevelPaths.Add(EGameType::GOW, TEXT("/Game/GOW/Levels/L_GOW"));
	GameLevelPaths.Add(EGameType::SpiderMan, TEXT("/Game/SpiderMan/Levels/L_SpiderMan"));
	GameLevelPaths.Add(EGameType::Control, TEXT("/Game/Control/Levels/L_Control"));
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
