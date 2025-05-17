#include "GoW/Character/GoWCharacter.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"

AGoWCharacter::AGoWCharacter()
{
    // Create the God of War specific attribute set
    GoWAttributeSet = CreateDefaultSubobject<UGoWAttributeSet>(TEXT("GoWAttributeSet"));
}

void AGoWCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize God of War specific abilities
    InitializeAbilities();
}

void AGoWCharacter::InitializeAbilities()
{
    Super::InitializeAbilities();
    
    // Initialize God of War specific abilities here
}

void AGoWCharacter::OnGameSwitched_Implementation(EGameType GameType)
{
    Super::OnGameSwitched_Implementation(GameType);
    
    if (GameType == EGameType::GOW)
    {
        UE_LOG(LogBaseCharacter, Log, TEXT("Switched to God of War gameplay"));
        // Apply God of War specific settings
    }
}