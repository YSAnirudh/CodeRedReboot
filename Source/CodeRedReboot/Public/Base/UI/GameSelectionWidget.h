#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameSelectionWidget.generated.h"

/**
 * Widget for selecting which game to play with carousel navigation
 */
UCLASS()
class CODEREDREBOOT_API UGameSelectionWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    virtual void NativeConstruct() override;
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void SelectGame(int32 GameIndex);
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void PlaySelectedGame();
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void ReturnToMainMenu();
    
    // Carousel navigation functions
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void NavigateLeft();
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void NavigateRight();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnGameSelected(EGameType GameType);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnReturnToMainMenu();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void UpdateVisibleGameCards();
    
protected:
    UPROPERTY(BlueprintReadWrite, Category = "Game Selection")
    EGameType SelectedGameType;
    
    // Array of all available games
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Selection")
    TArray<EGameType> AvailableGames;
    
    // Current index in the carousel
    UPROPERTY(BlueprintReadWrite, Category = "Game Selection")
    int32 CurrentIndex;
    
    // Maximum number of visible game cards
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Selection")
    int32 MaxVisibleCards = 3;
    
    // Get the indices of the currently visible games
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    TArray<int32> GetVisibleGameIndices() const;
    
    // Get the game types of the currently visible games
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    TArray<EGameType> GetVisibleGames() const;
};