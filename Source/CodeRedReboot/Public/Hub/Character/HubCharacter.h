#pragma once

#include "CoreMinimal.h"
#include "Base/Character/BaseCharacter.h"
#include "HubCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API AHubCharacter : public ABaseCharacter
{
    GENERATED_BODY()
    
public:
    AHubCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeAbilities() override;
    virtual void OnGameSwitched_Implementation(EGameType GameType) override;
};