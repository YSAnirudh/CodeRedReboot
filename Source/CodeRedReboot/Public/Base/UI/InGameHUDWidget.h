#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InGameHUDWidget.generated.h"

class UCommonButtonBase;
class UCommonTextBlock;
class UProgressBar;

/**
 * Base HUD widget for in-game display
 * Uses CommonUI for better navigation and interaction
 */
UCLASS()
class CODEREDREBOOT_API UInGameHUDWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
    
public:
    UInGameHUDWidget();
    
    // UUserWidget overrides
    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    
    /** Returns to the hub/main menu */
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ReturnToHub();
    
    /** Updates the health bar display */
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealthBar(float CurrentHealth, float MaxHealth);
    
    /** Updates game-specific attributes */
    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void UpdateGameSpecificAttributes();
    
protected:
    /** Health bar progress indicator */
    UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (BindWidget))
    UProgressBar* HealthBar = nullptr;
    
    /** Return to hub button */
    UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (BindWidget))
    UCommonButtonBase* ReturnToHubButton = nullptr;
    
    /** Health text display */
    UPROPERTY(BlueprintReadOnly, Category = "HUD", meta = (BindWidget))
    UCommonTextBlock* HealthText = nullptr;
    
    /** Handle return to hub button click */
    UFUNCTION()
    void HandleReturnToHubClicked();
    
private:
    /** Bind input events */
    void BindInputEvents();
    
    /** Unbind input events */
    void UnbindInputEvents();
};