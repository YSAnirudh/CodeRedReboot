#include "Control/Character/ControlCharacter.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"

AControlCharacter::AControlCharacter()
{
    // Create the Control specific attribute set
    ControlAttributeSet = CreateDefaultSubobject<UControlAttributeSet>(TEXT("ControlAttributeSet"));
}

void AControlCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize Control specific abilities
    InitializeAbilities();
}

void AControlCharacter::InitializeAbilities()
{
    Super::InitializeAbilities();
    
    // Initialize Control specific abilities here
}

void AControlCharacter::OnGameSwitched_Implementation(EGameType GameType)
{
    Super::OnGameSwitched_Implementation(GameType);
    
    if (GameType == EGameType::Control)
    {
        UE_LOG(LogBaseCharacter, Log, TEXT("Switched to Control gameplay"));
        // Apply Control specific settings
    }
}