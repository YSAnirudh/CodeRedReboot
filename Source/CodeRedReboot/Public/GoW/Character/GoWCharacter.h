#pragma once

#include "CoreMinimal.h"
#include "Base/Character/BaseCharacter.h"
#include "GOW/AbilitySystem/GOWAttributeSet.h"
#include "GOWCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API AGOWCharacter : public ABaseCharacter
{
    GENERATED_BODY()
    
public:
    AGOWCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeAbilities() override;
    virtual void OnGameSwitched_Implementation(EGameType GameType) override;

    UPROPERTY()
    UGOWAttributeSet* GOWAttributeSet;
};