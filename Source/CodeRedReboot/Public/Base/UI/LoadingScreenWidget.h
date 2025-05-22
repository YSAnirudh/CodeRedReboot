#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LoadingScreenWidget.generated.h"

class UCommonTextBlock;
class UProgressBar;

/**
 * Loading screen widget using CommonUI
 * Displays loading progress and status text
 */
UCLASS()
class CODEREDREBOOT_API ULoadingScreenWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()
    
public:
    ULoadingScreenWidget();
    
    // UUserWidget overrides
    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;

    /** Sets the loading progress (0.0 to 1.0) */
    UFUNCTION(BlueprintCallable, Category = "Loading")
    void SetLoadingProgress(float Progress);

    /** Sets the loading status text */
    UFUNCTION(BlueprintCallable, Category = "Loading")
    void SetLoadingText(const FText& Text);

    /** Called when loading is complete */
    UFUNCTION(BlueprintImplementableEvent, Category = "Loading")
    void OnLoadingComplete();
    
    /** Starts the fade-out animation when loading is complete */
    UFUNCTION(BlueprintCallable, Category = "Loading")
    void CompleteLoading();

protected:
    /** Progress bar for loading status */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* LoadingProgressBar = nullptr;

    /** Text block for loading status */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UCommonTextBlock* LoadingTextBlock = nullptr;
    
    /** Whether loading is complete */
    UPROPERTY(BlueprintReadOnly, Category = "Loading")
    bool bIsLoadingComplete = false;
};