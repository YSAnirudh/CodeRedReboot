#include "Control/AbilitySystem/ControlAttributeSet.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "BaseLogChannels.h"

UControlAttributeSet::UControlAttributeSet()
{
    PsychicEnergy = 100.0f;
    MaxPsychicEnergy = 100.0f;
    TelekineticStrength = 50.0f;
    ShieldDurability = 100.0f;
}

void UControlAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetPsychicEnergyAttribute())
    {
        SetPsychicEnergy(FMath::Clamp(GetPsychicEnergy(), 0.0f, GetMaxPsychicEnergy()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxPsychicEnergyAttribute())
    {
        SetMaxPsychicEnergy(FMath::Max(GetMaxPsychicEnergy(), 0.0f));
        SetPsychicEnergy(FMath::Clamp(GetPsychicEnergy(), 0.0f, GetMaxPsychicEnergy()));
    }
}