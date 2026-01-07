#include "Base/UI/GameCardWidget.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

UGameCardWidget::UGameCardWidget()
{
    // Configure CommonUI button behavior
    bToggleable = false;
    bApplyAlphaOnDisable = true;
}

void UGameCardWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UGameCardWidget::NativeOnCurrentTextStyleChanged()
{
    Super::NativeOnCurrentTextStyleChanged();
    
    // Apply text style changes to child text blocks
    if (GameTitleText)
    {
        GameTitleText->SetStyle(GetCurrentTextStyleClass());
    }
    
    if (GameDescriptionText)
    {
        GameDescriptionText->SetStyle(GetCurrentTextStyleClass());
    }
}

void UGameCardWidget::NativeOnSelected(bool bIsSelected)
{
    Super::NativeOnSelected(bIsSelected);
    
    // Scale up slightly when selected for visual feedback
    SetRenderScale(bIsSelected ? FVector2D(1.05f, 1.05f) : FVector2D(1.0f, 1.0f));
}

void UGameCardWidget::NativeOnClicked()
{
    Super::NativeOnClicked();

    UMultiGameInstance* GameInstance = Cast<UMultiGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        GameInstance->SwitchGame(GameInfo.GameType);
    }
}

void UGameCardWidget::SetGameInfo(const FGameInformation& InGameInfo)
{
    GameDescriptionText->SetText(FText::FromString(InGameInfo.GameDescription));
    GameTitleText->SetText(FText::FromString(InGameInfo.GameName));
    GameThumbnail = InGameInfo.GameThumbnail;
    GameInfo = InGameInfo;
}