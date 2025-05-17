#include "GOW/AbilitySystem/GOWAttributeSet.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "BaseLogChannels.h"

UGOWAttributeSet::UGOWAttributeSet()
{
    Rage = 0.0f;
    MaxRage = 100.0f;
    WeaponDamage = 20.0f;
    DefenseRating = 10.0f;
}

void UGOWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetRageAttribute())
    {
        SetRage(FMath::Clamp(GetRage(), 0.0f, GetMaxRage()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxRageAttribute())
    {
        SetMaxRage(FMath::Max(GetMaxRage(), 0.0f));
        SetRage(FMath::Clamp(GetRage(), 0.0f, GetMaxRage()));
    }
}