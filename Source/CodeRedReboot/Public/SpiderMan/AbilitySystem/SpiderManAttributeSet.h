#pragma once

#include "CoreMinimal.h"
#include "Base/AbilitySystem/BaseAttributeSet.h"
#include "SpiderManAttributeSet.generated.h"

UCLASS()
class CODEREDREBOOT_API USpiderManAttributeSet : public UBaseAttributeSet
{
    GENERATED_BODY()
    
public:
    USpiderManAttributeSet();
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData WebFluid;
    ATTRIBUTE_ACCESSORS(USpiderManAttributeSet, WebFluid);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData MaxWebFluid;
    ATTRIBUTE_ACCESSORS(USpiderManAttributeSet, MaxWebFluid);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData SwingMomentum;
    ATTRIBUTE_ACCESSORS(USpiderManAttributeSet, SwingMomentum);
    
    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    FGameplayAttributeData ComboMultiplier;
    ATTRIBUTE_ACCESSORS(USpiderManAttributeSet, ComboMultiplier);
    
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};