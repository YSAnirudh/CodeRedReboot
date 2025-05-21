#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * Main menu widget that serves as the entry point to the game
 */
UCLASS()
class CODEREDREBOOT_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowGameSelection();
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowOptions();
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    void QuitGame();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnShowGameSelection();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnShowOptions();
};