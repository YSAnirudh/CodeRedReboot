#include "Base/UI/InGameHUDWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"
#include "Components/ProgressBar.h"
#include "BaseLogChannels.h"

UInGameHUDWidget::UInGameHUDWidget()
{
    // Configure CommonUI behavior
    SetIsFocusable(true);
}

void UInGameHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (ReturnToHubButton)
    {
        ReturnToHubButton->OnClicked().AddUObject(this, &UInGameHUDWidget::HandleReturnToHubClicked);
    }
}

void UInGameHUDWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    
    // Bind input events when activated
    BindInputEvents();
}

void UInGameHUDWidget::NativeOnDeactivated()
{
    // Unbind input events when deactivated
    UnbindInputEvents();
    
    Super::NativeOnDeactivated();
}

void UInGameHUDWidget::BindInputEvents()
{
    // Register with the input subsystem for navigation events
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UInGameHUDWidget::UnbindInputEvents()
{
    // Unregister from the input subsystem
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UInGameHUDWidget::ReturnToHub()
{
    ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
    if (PlayerController)
    {
        PlayerController->ReturnToHub();
        UE_LOG(LogBaseUI, Log, TEXT("Returning to hub from game"));
    }
}

void UInGameHUDWidget::HandleReturnToHubClicked()
{
    ReturnToHub();
}

void UInGameHUDWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
    if (HealthBar)
    {
        const float HealthPercent = (MaxHealth > 0.0f) ? FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f) : 0.0f;
        HealthBar->SetPercent(HealthPercent);
    }
    
    if (HealthText)
    {
        FText HealthDisplay = FText::Format(NSLOCTEXT("InGameHUD", "HealthFormat", "{0}/{1}"), 
            FText::AsNumber(FMath::FloorToInt(CurrentHealth)), 
            FText::AsNumber(FMath::FloorToInt(MaxHealth)));
        HealthText->SetText(HealthDisplay);
    }
}