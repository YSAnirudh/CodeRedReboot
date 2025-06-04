#include "Base/UI/MainMenuWidget.h"
#include "CommonButtonBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseLogChannels.h"

UMainMenuWidget::UMainMenuWidget()
{
    // Configure CommonUI behavior
    SetIsFocusable(true);
}

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Setup button click handlers
    if (PlayButton)
    {
        PlayButton->OnClicked().AddUObject(this, &UMainMenuWidget::HandlePlayButtonClicked);
    }
    
    if (OptionsButton)
    {
        OptionsButton->OnClicked().AddUObject(this, &UMainMenuWidget::HandleOptionsButtonClicked);
    }
    
    if (QuitButton)
    {
        QuitButton->OnClicked().AddUObject(this, &UMainMenuWidget::HandleQuitButtonClicked);
    }
}

void UMainMenuWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    
    // Bind input events when activated
    BindInputEvents();
    
    // Set initial focus when activated
    if (PlayButton)
    {
        PlayButton->SetFocus();
    }
}

void UMainMenuWidget::NativeOnDeactivated()
{
    // Unbind input events when deactivated
    UnbindInputEvents();
    
    Super::NativeOnDeactivated();
}

void UMainMenuWidget::BindInputEvents()
{
    // Register with the input subsystem for navigation events
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UMainMenuWidget::UnbindInputEvents()
{
    // Unregister from the input subsystem
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
    }
}

void UMainMenuWidget::HandlePlayButtonClicked()
{
    ShowGameSelection();
}

void UMainMenuWidget::HandleOptionsButtonClicked()
{
    ShowOptions();
}

void UMainMenuWidget::HandleQuitButtonClicked()
{
    QuitGame();
}

void UMainMenuWidget::ShowGameSelection()
{
    OnShowGameSelection();
}

void UMainMenuWidget::ShowOptions()
{
    OnShowOptions();
}

void UMainMenuWidget::QuitGame()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
    }
}