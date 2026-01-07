#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "GameCardWidget.generated.h"

class UCommonTextBlock;
class UImage;

/**
 * Widget representing a single game option in the selection screen
 * Uses CommonUI for better navigation and interaction
 */
UCLASS()
class CODEREDREBOOT_API UGameCardWidget : public UCommonButtonBase
{
    GENERATED_BODY()
    
public:
    UGameCardWidget();
    
    /** Sets the game type and updates the display */
    UFUNCTION(BlueprintCallable, Category = "Game Card")
    void SetGameInfo(const FGameInformation& GameInfo);
    
    /** Gets the current game type */
    UFUNCTION(BlueprintPure, Category = "Game Card")
    const FGameInformation& GetGameInfo() const { return GameInfo; }

    /** Gets the current game type */
    UFUNCTION(BlueprintPure, Category = "Game Card")
    EGameType GetGameType() const { return GameInfo.GameType; }
    
    // CommonUI overrides
    virtual void NativePreConstruct() override;
    // Common Button overrides
    virtual void NativeOnCurrentTextStyleChanged() override;
    virtual void NativeOnSelected(bool bIsSelected) override;
    virtual void NativeOnClicked() override;
    
protected:
    /** The game type this card represents */
    UPROPERTY(BlueprintReadOnly, Category = "Game Card")
    FGameInformation GameInfo;
    
    /** Title text for the game */
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    UCommonTextBlock* GameTitleText = nullptr;
    
    /** Description text for the game */
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    UCommonTextBlock* GameDescriptionText = nullptr;
    
    /** Thumbnail image for the game */
    UPROPERTY(BlueprintReadOnly, Category = "Game Card", meta = (BindWidget))
    UImage* GameThumbnail = nullptr;
};