#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameCardWidget.generated.h"

/**
 * Widget representing a single game option in the selection screen
 */
UCLASS()
class CODEREDREBOOT_API UGameCardWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Game Card")
    void SetGameType(EGameType InGameType);
    
    UFUNCTION(BlueprintCallable, Category = "Game Card")
    EGameType GetGameType() const { return GameType; }
    
    UFUNCTION(BlueprintCallable, Category = "Game Card")
    void SetSelected(bool bIsSelected);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Card")
    void OnSelected(bool bIsSelected);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Card")
    void UpdateGameInfo();
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "Game Card")
    EGameType GameType;
    
    UPROPERTY(BlueprintReadOnly, Category = "Game Card")
    bool bSelected;
    
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    class UTextBlock* GameTitleText;
    
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    class UTextBlock* GameDescriptionText;
    
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    class UImage* GameThumbnail;
};