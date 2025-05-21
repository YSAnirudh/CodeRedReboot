#include "GOW/Character/GOWCharacter.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"

AGOWCharacter::AGOWCharacter()
{
    // Create the God of War specific attribute set
    GOWAttributeSet = CreateDefaultSubobject<UGOWAttributeSet>(TEXT("GOWAttributeSet"));
}

void AGOWCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize God of War specific abilities
    InitializeAbilities();
}

void AGOWCharacter::InitializeAbilities()
{
    Super::InitializeAbilities();
    
    // Initialize God of War specific abilities here
}

void AGOWCharacter::OnGameSwitched_Implementation(EGameType GameType)
{
    Super::OnGameSwitched_Implementation(GameType);
    
    if (GameType == EGameType::GOW)
    {
        UE_LOG(LogBaseCharacter, Log, TEXT("Switched to God of War gameplay"));
        // Apply God of War specific settings
    }
}