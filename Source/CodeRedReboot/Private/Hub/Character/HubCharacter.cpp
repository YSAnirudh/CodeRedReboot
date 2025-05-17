#include "Hub/Character/HubCharacter.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"

AHubCharacter::AHubCharacter()
{
    // Hub character setup
}

void AHubCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize Hub specific abilities
    InitializeAbilities();
}

void AHubCharacter::InitializeAbilities()
{
    Super::InitializeAbilities();
    
    // Initialize Hub specific abilities here
}

void AHubCharacter::OnGameSwitched_Implementation(EGameType GameType)
{
    Super::OnGameSwitched_Implementation(GameType);
    
    if (GameType == EGameType::Hub)
    {
        UE_LOG(LogBaseCharacter, Log, TEXT("Switched to Hub gameplay"));
        // Apply Hub specific settings
    }
}