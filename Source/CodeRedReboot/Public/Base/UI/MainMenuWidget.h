#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MainMenuWidget.generated.h"

class UCommonButtonBase;
class UCommonActivatableWidgetStack;

/**
 * Main menu widget that serves as the entry point to the game
 * Uses CommonUI for better navigation and interaction
 */
UCLASS()
class CODEREDREBOOT_API UMainMenuWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
    
public:
    UMainMenuWidget();
    
    // UUserWidget overrides
    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    
    /** Shows the game selection screen */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowGameSelection();
    
    /** Shows the options screen */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowOptions();
    
    /** Quits the game */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void QuitGame();
    
    /** Called when showing game selection */
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnShowGameSelection();
    
    /** Called when showing options */
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnShowOptions();
    
protected:
    /** Play button */
    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (BindWidget))
    UCommonButtonBase* PlayButton = nullptr;
    
    /** Options button */
    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (BindWidget))
    UCommonButtonBase* OptionsButton = nullptr;
    
    /** Quit button */
    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (BindWidget))
    UCommonButtonBase* QuitButton = nullptr;
    
    /** Widget stack for menu navigation */
    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (BindWidget))
    UCommonActivatableWidgetStack* MenuStack = nullptr;
    
    /** Handle play button click */
    UFUNCTION()
    void HandlePlayButtonClicked();
    
    /** Handle options button click */
    UFUNCTION()
    void HandleOptionsButtonClicked();
    
    /** Handle quit button click */
    UFUNCTION()
    void HandleQuitButtonClicked();
    
private:
    /** Bind input events */
    void BindInputEvents();
    
    /** Unbind input events */
    void UnbindInputEvents();
};