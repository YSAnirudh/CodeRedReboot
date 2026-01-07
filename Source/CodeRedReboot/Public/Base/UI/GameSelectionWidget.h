#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameSelectionWidget.generated.h"

class UCommonButtonBase;
class UCommonTileView;
class UGameCardWidget;
class UCarousel;

/**
 * Widget for selecting which game to play with carousel navigation
 * Uses CommonUI for better navigation and interaction
 */
UCLASS()
class CODEREDREBOOT_API UGameSelectionWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
    
public:
    UGameSelectionWidget();
    
    // UUserWidget overrides
    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    
    /** Launches the currently selected game */
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void PlaySelectedGame();
    
    /** Returns to the main menu */
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void ReturnToMainMenu();
    
    /** Called when a game is selected */
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnGameSelected(EGameType GameType);
    
    /** Called when returning to main menu */
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnReturnToMainMenu();
    
protected:
    /** Tile view for displaying game cards */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCarousel* GameCarousel = nullptr;
    
    /** Button to play the selected game */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCommonButtonBase* PlayButton = nullptr;
    
    /** Button to return to main menu */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCommonButtonBase* BackButton = nullptr;
    
    /** Handle play button click */
    UFUNCTION()
    void HandlePlayButtonClicked();
    
    /** Handle back button click */
    UFUNCTION()
    void HandleBackButtonClicked();
    
private:
    /** Bind input events */
    void BindInputEvents();
    
    /** Unbind input events */
    void UnbindInputEvents();
};