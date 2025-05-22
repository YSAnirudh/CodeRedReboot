#include "Base/UI/GameCardWidget.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

UGameCardWidget::UGameCardWidget()
{
    // Configure CommonUI button behavior
    SelectionGroup = TEXT("GameCards");
    bToggleable = false;
    bApplyAlphaOnDisable = true;
    bWrapButtonText = true;
    
    // Set default style tags
    SetStyle(FName("GameCardButton"));
}

void UGameCardWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    
    // Update the game info when constructed
    UpdateGameInfo();
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

void UGameCardWidget::SetGameType(EGameType InGameType)
{
    if (GameType != InGameType)
    {
        GameType = InGameType;
        UpdateGameInfo();
    }
}