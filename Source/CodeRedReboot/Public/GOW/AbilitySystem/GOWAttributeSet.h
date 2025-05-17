#pragma once

#include "CoreMinimal.h"
#include "Base/AbilitySystem/BaseAttributeSet.h"
#include "GOWAttributeSet.generated.h"

UCLASS()
class CODEREDREBOOT_API UGOWAttributeSet : public UBaseAttributeSet
{
    GENERATED_BODY()
    
public:
    UGOWAttributeSet();
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData Rage;
    ATTRIBUTE_ACCESSORS(UGOWAttributeSet, Rage);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData MaxRage;
    ATTRIBUTE_ACCESSORS(UGOWAttributeSet, MaxRage);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData WeaponDamage;
    ATTRIBUTE_ACCESSORS(UGOWAttributeSet, WeaponDamage);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData DefenseRating;
    ATTRIBUTE_ACCESSORS(UGOWAttributeSet, DefenseRating);
    
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};