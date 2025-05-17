#pragma once

#include "CoreMinimal.h"
#include "Base/Character/BaseCharacter.h"
#include "SpiderMan/AbilitySystem/SpiderManAttributeSet.h"
#include "SpiderManCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API ASpiderManCharacter : public ABaseCharacter
{
    GENERATED_BODY()
    
public:
    ASpiderManCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeAbilities() override;
    virtual void OnGameSwitched_Implementation(EGameType GameType) override;

    UPROPERTY()
    USpiderManAttributeSet* SpiderManAttributeSet;
};