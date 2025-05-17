#include "SpiderMan/Character/SpiderManCharacter.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"

ASpiderManCharacter::ASpiderManCharacter()
{
    // Create the Spider-Man specific attribute set
    SpiderManAttributeSet = CreateDefaultSubobject<USpiderManAttributeSet>(TEXT("SpiderManAttributeSet"));
}

void ASpiderManCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize Spider-Man specific abilities
    InitializeAbilities();
}

void ASpiderManCharacter::InitializeAbilities()
{
    Super::InitializeAbilities();
    
    // Initialize Spider-Man specific abilities here
}

void ASpiderManCharacter::OnGameSwitched_Implementation(EGameType GameType)
{
    Super::OnGameSwitched_Implementation(GameType);
    
    if (GameType == EGameType::SpiderMan)
    {
        UE_LOG(LogBaseCharacter, Log, TEXT("Switched to Spider-Man gameplay"));
        // Apply Spider-Man specific settings
    }
}