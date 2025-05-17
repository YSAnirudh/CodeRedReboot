#pragma once

#include "CoreMinimal.h"
#include "Base/Character/BaseCharacter.h"
#include "Control/AbilitySystem/ControlAttributeSet.h"
#include "ControlCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API AControlCharacter : public ABaseCharacter
{
    GENERATED_BODY()
    
public:
    AControlCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeAbilities() override;
    virtual void OnGameSwitched_Implementation(EGameType GameType) override;

    UPROPERTY()
    UControlAttributeSet* ControlAttributeSet;
};