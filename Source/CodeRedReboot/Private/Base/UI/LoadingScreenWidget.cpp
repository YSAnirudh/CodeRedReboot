#include "Base/UI/LoadingScreenWidget.h"
#include "Components/ProgressBar.h"
#include "CommonTextBlock.h"
#include "Animation/WidgetAnimation.h"

ULoadingScreenWidget::ULoadingScreenWidget()
{
    // Loading screens typically don't need input
    SetIsFocusable(false);
}

void ULoadingScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Initialize with 0 progress
    if (LoadingProgressBar)
    {
        LoadingProgressBar->SetPercent(0.0f);
    }
    
    // Set default loading text
    if (LoadingTextBlock)
    {
        LoadingTextBlock->SetText(NSLOCTEXT("LoadingScreen", "DefaultLoadingText", "Loading..."));
    }
    
    bIsLoadingComplete = false;
}

void ULoadingScreenWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    
    // Reset loading state when activated
    bIsLoadingComplete = false;
    
    if (LoadingProgressBar)
    {
        LoadingProgressBar->SetPercent(0.0f);
    }
}

void ULoadingScreenWidget::SetLoadingProgress(float Progress)
{
    if (LoadingProgressBar)
    {
        const float ClampedProgress = FMath::Clamp(Progress, 0.0f, 1.0f);
        LoadingProgressBar->SetPercent(ClampedProgress);
        
        // Auto-complete loading if we reach 100%
        if (ClampedProgress >= 1.0f && !bIsLoadingComplete)
        {
            CompleteLoading();
        }
    }
}

void ULoadingScreenWidget::SetLoadingText(const FText& Text)
{
    if (LoadingTextBlock)
    {
        LoadingTextBlock->SetText(Text);
    }
}

void ULoadingScreenWidget::CompleteLoading()
{
    if (!bIsLoadingComplete)
    {
        bIsLoadingComplete = true;
        OnLoadingComplete();
    }
}