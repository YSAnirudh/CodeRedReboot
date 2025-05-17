#pragma once

#include "CoreMinimal.h"
#include "Base/Character/BaseCharacter.h"
#include "GoW/AbilitySystem/GoWAttributeSet.h"
#include "GoWCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API AGoWCharacter : public ABaseCharacter
{
    GENERATED_BODY()
    
public:
    AGoWCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeAbilities() override;
    virtual void OnGameSwitched_Implementation(EGameType GameType) override;

    UPROPERTY()
    UGoWAttributeSet* GoWAttributeSet;
};