#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameSelectionWidget.generated.h"

class UCommonButtonBase;
class UCommonTileView;
class UGameCardWidget;

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
    
    /** Selects a game by index */
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void SelectGame(int32 GameIndex);
    
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
    /** Currently selected game type */
    UPROPERTY(BlueprintReadWrite, Category = "Game Selection")
    EGameType SelectedGameType = EGameType::None;
    
    /** Array of all available games */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Selection")
    TArray<EGameType> AvailableGames;
    
    /** Current index in the carousel */
    UPROPERTY(BlueprintReadWrite, Category = "Game Selection")
    int32 CurrentIndex = 0;
    
    /** Maximum number of visible game cards */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Selection", meta = (ClampMin = "1", ClampMax = "10"))
    int32 MaxVisibleCards = 3;
    
    /** Tile view for displaying game cards */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCommonTileView* GameTileView = nullptr;
    
    /** Button to play the selected game */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCommonButtonBase* PlayButton = nullptr;
    
    /** Button to return to main menu */
    UPROPERTY(BlueprintReadOnly, Category = "Game Selection", meta = (BindWidget))
    UCommonButtonBase* BackButton = nullptr;
    
    /** Get the indices of the currently visible games */
    UFUNCTION(BlueprintPure, Category = "Game Selection")
    TArray<int32> GetVisibleGameIndices() const;
    
    /** Get the game types of the currently visible games */
    UFUNCTION(BlueprintPure, Category = "Game Selection")
    TArray<EGameType> GetVisibleGames() const;
    
    /** Handle game card selection */
    UFUNCTION()
    void HandleGameCardClicked(UObject* Item);
    
    /** Handle play button click */
    UFUNCTION()
    void HandlePlayButtonClicked();
    
    /** Handle back button click */
    UFUNCTION()
    void HandleBackButtonClicked();
    
    /** Initialize the tile view with game cards */
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void InitializeGameTileView();
    
private:
    /** Bind input events */
    void BindInputEvents();
    
    /** Unbind input events */
    void UnbindInputEvents();
};