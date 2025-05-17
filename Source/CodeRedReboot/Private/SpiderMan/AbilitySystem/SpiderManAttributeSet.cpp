#include "SpiderMan/AbilitySystem/SpiderManAttributeSet.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "BaseLogChannels.h"

USpiderManAttributeSet::USpiderManAttributeSet()
{
    WebFluid = 100.0f;
    MaxWebFluid = 100.0f;
    SwingMomentum = 0.0f;
    ComboMultiplier = 1.0f;
}

void USpiderManAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetWebFluidAttribute())
    {
        SetWebFluid(FMath::Clamp(GetWebFluid(), 0.0f, GetMaxWebFluid()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxWebFluidAttribute())
    {
        SetMaxWebFluid(FMath::Max(GetMaxWebFluid(), 0.0f));
        SetWebFluid(FMath::Clamp(GetWebFluid(), 0.0f, GetMaxWebFluid()));
    }
}