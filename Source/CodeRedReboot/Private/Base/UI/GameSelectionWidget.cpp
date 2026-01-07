#include "Base/UI/GameSelectionWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "Base/UI/GameCardWidget.h"
#include "Base/UI/Carousel/Carousel.h"
#include "BaseLogChannels.h"
#include "CommonButtonBase.h"
#include "CommonTileView.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"

UGameSelectionWidget::UGameSelectionWidget()
{
    // Configure CommonUI behavior
    SetIsFocusable(true);
}

void UGameSelectionWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Setup button click handlers
    if (PlayButton)
    {
        PlayButton->OnClicked().AddUObject(this, &UGameSelectionWidget::HandlePlayButtonClicked);
    }
    
    if (BackButton)
    {
        BackButton->OnClicked().AddUObject(this, &UGameSelectionWidget::HandleBackButtonClicked);
    }
}

void UGameSelectionWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    
    // Bind input events when activated
    BindInputEvents();
    
    // Set initial focus when activated
    if (GameCarousel)
    {
        // Set keyboard focus to the selected item
        if (UCommonButtonBase* SelectedButton = Cast<UCommonButtonBase>(GameCarousel->GetSelectedGame()))
        {
            SelectedButton->SetFocus();
        }
    }
}

void UGameSelectionWidget::NativeOnDeactivated()
{
    // Unbind input events when deactivated
    UnbindInputEvents();
    
    Super::NativeOnDeactivated();
}

void UGameSelectionWidget::HandlePlayButtonClicked()
{
    PlaySelectedGame();
}

void UGameSelectionWidget::HandleBackButtonClicked()
{
    ReturnToMainMenu();
}

void UGameSelectionWidget::BindInputEvents()
{
    // Register with the input subsystem for navigation events
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UGameSelectionWidget::UnbindInputEvents()
{
    // Unregister from the input subsystem
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UGameSelectionWidget::PlaySelectedGame()
{
    ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
    if (PlayerController)
    {
        const EGameType SelectedGameType = GameCarousel->GetSelectedGame()->GetGameType();
        PlayerController->SwitchGame(SelectedGameType);
        UE_LOG(LogBaseUI, Log, TEXT("Switching to game: %s"), *UEnum::GetValueAsString(SelectedGameType));
    }
}

void UGameSelectionWidget::ReturnToMainMenu()
{
    OnReturnToMainMenu();
}
