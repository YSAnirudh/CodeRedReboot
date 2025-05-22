#include "Base/UI/GameSelectionWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "BaseLogChannels.h"

void UGameSelectionWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Initialize available games if empty
    if (AvailableGames.Num() == 0)
    {
        AvailableGames.Add(EGameType::GOW);
        AvailableGames.Add(EGameType::SpiderMan);
        AvailableGames.Add(EGameType::Control);
    }
    
    // Start at the first game
    CurrentIndex = 0;
    
    // Select the first game
    if (AvailableGames.Num() > 0)
    {
        SelectGame(CurrentIndex);
    }
    
    // Update the visible game cards
    UpdateVisibleGameCards();
}

void UGameSelectionWidget::SelectGame(int32 GameIndex)
{
    const EGameType GameType = AvailableGames[GameIndex];
    if (GameType == EGameType::None)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Invalid game type at index %d"), GameIndex);
        return;
    }
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

void UGameSelectionWidget::NavigateLeft()
{
    if (AvailableGames.Num() == 0)
    {
        return;
    }
    
    // Move left with wrap-around
    CurrentIndex = (CurrentIndex - 1 + AvailableGames.Num()) % AvailableGames.Num();
    
    // Select the new current game
    SelectGame(CurrentIndex);
    
    // Update the visible game cards
    UpdateVisibleGameCards();
}

void UGameSelectionWidget::NavigateRight()
{
    if (AvailableGames.Num() == 0)
    {
        return;
    }
    
    // Move right with wrap-around
    CurrentIndex = (CurrentIndex + 1) % AvailableGames.Num();
    
    // Select the new current game
    SelectGame(CurrentIndex);
    
    // Update the visible game cards
    UpdateVisibleGameCards();
}

TArray<int32> UGameSelectionWidget::GetVisibleGameIndices() const
{
    TArray<int32> VisibleIndices;
    
    if (AvailableGames.Num() == 0)
    {
        return VisibleIndices;
    }
    
    // Calculate how many cards to show (up to MaxVisibleCards)
    int32 NumToShow = FMath::Min(MaxVisibleCards, AvailableGames.Num());
    
    // Calculate the starting index
    int32 StartIndex = 0;
    
    if (NumToShow == MaxVisibleCards)
    {
        // If we're showing the max number of cards, center the current selection
        StartIndex = CurrentIndex - (NumToShow / 2);
        
        // Wrap around if needed
        while (StartIndex < 0)
        {
            StartIndex += AvailableGames.Num();
        }
    }
    
    // Add the visible indices with wrap-around
    for (int32 i = 0; i < NumToShow; i++)
    {
        int32 Index = (StartIndex + i) % AvailableGames.Num();
        VisibleIndices.Add(Index);
    }
    
    return VisibleIndices;
}

TArray<EGameType> UGameSelectionWidget::GetVisibleGames() const
{
    TArray<EGameType> VisibleGames;
    
    TArray<int32> VisibleIndices = GetVisibleGameIndices();
    for (int32 Index : VisibleIndices)
    {
        VisibleGames.Add(AvailableGames[Index]);
    }
    
    return VisibleGames;
}