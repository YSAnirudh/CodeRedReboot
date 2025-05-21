#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameSelectionWidget.generated.h"

/**
 * Widget for selecting which game to play
 */
UCLASS()
class CODEREDREBOOT_API UGameSelectionWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void SelectGame(EGameType GameType);
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void PlaySelectedGame();
    
    UFUNCTION(BlueprintCallable, Category = "Game Selection")
    void ReturnToMainMenu();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnGameSelected(EGameType GameType);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Selection")
    void OnReturnToMainMenu();
    
protected:
    UPROPERTY(BlueprintReadWrite, Category = "Game Selection")
    EGameType SelectedGameType;
};