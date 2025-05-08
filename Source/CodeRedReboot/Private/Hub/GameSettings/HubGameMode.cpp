// Fill out your copyright notice in the Description page of Project Settings.


#include "Hub/GameSettings/HubGameMode.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "BaseLogChannels.h"

AHubGameMode::AHubGameMode()
{
}

void AHubGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeHubSystems();

	UE_LOG(LogHubGameMode, Log, TEXT("Hub Game mode initialized"));
}

void AHubGameMode::InitializeHubSystems()
{
}

void AHubGameMode::OnPlayerEnteredHub(APlayerController* PlayerController)
{
	ABasePlayerController* BasePC = Cast<ABasePlayerController>(PlayerController);
	if (BasePC)
	{
		BasePC->HideLoadingScreen();

		UE_LOG(LogHubGameMode, Log, TEXT("Player entered hub"));
	}
}
