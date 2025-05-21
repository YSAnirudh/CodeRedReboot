#include "Base/UI/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseLogChannels.h"

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