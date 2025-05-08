// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API ULoadingScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Loading")
	void SetLoadingProgress(float Progress);

	UFUNCTION(BlueprintCallable, Category = "Loading")
	void SetLoadingText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent, Category = "Loading")
	void OnLoadingComplete();

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* LoadingProgressBar = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LoadingTextBlock = nullptr;
};
