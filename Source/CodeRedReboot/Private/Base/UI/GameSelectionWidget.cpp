#include "Base/UI/GameSelectionWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "BaseLogChannels.h"

void UGameSelectionWidget::SelectGame(EGameType GameType)
{
    SelectedGameType = GameType;
    OnGameSelected(GameType);
    
    UE_LOG(LogBaseUI, Log, TEXT("Game selected: %s"), *UEnum::GetValueAsString(GameType));
}

void UGameSelectionWidget::PlaySelectedGame()
{
    ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
    if (PlayerController)
    {
        PlayerController->SwitchGame(SelectedGameType);
        UE_LOG(LogBaseUI, Log, TEXT("Switching to game: %s"), *UEnum::GetValueAsString(SelectedGameType));
    }
}

void UGameSelectionWidget::ReturnToMainMenu()
{
    OnReturnToMainMenu();
}