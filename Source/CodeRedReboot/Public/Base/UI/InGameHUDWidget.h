#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

/**
 * Base HUD widget for in-game display
 */
UCLASS()
class CODEREDREBOOT_API UInGameHUDWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ReturnToHub();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void UpdateHealthBar(float CurrentHealth, float MaxHealth);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void UpdateGameSpecificAttributes();
    
protected:
    virtual void NativeConstruct() override;
    
    UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (BindWidget))
    class UProgressBar* HealthBar;
    
    UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (BindWidget))
    class UButton* ReturnToHubButton;
    
    UFUNCTION()
    void OnReturnToHubClicked();
};