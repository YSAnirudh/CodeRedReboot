#pragma once

#include "CoreMinimal.h"
#include "Base/AbilitySystem/BaseAttributeSet.h"
#include "ControlAttributeSet.generated.h"

UCLASS()
class CODEREDREBOOT_API UControlAttributeSet : public UBaseAttributeSet
{
    GENERATED_BODY()
    
public:
    UControlAttributeSet();
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData PsychicEnergy;
    ATTRIBUTE_ACCESSORS(UControlAttributeSet, PsychicEnergy);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData MaxPsychicEnergy;
    ATTRIBUTE_ACCESSORS(UControlAttributeSet, MaxPsychicEnergy);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData TelekineticStrength;
    ATTRIBUTE_ACCESSORS(UControlAttributeSet, TelekineticStrength);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData ShieldDurability;
    ATTRIBUTE_ACCESSORS(UControlAttributeSet, ShieldDurability);
    
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};