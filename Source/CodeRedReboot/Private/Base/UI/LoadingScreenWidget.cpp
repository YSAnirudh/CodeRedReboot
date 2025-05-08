// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UI/LoadingScreenWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ULoadingScreenWidget::SetLoadingProgress(float Progress)
{
	if (LoadingProgressBar)
	{
		LoadingProgressBar->SetPercent(FMath::Clamp(Progress, 0.0f, 1.0f));
	}
}

void ULoadingScreenWidget::SetLoadingText(const FText& Text)
{
	if (LoadingTextBlock)
	{
		LoadingTextBlock->SetText(Text);
	}
}
