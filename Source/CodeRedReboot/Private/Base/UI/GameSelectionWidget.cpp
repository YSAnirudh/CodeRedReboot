#include "Base/UI/GameSelectionWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "Base/UI/GameCardWidget.h"
#include "BaseLogChannels.h"
#include "CommonButtonBase.h"
#include "CommonTileView.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"

UGameSelectionWidget::UGameSelectionWidget()
{
    // Configure CommonUI behavior
    SetInputActionProcessingEnabled(true);
    SetIsFocusable(true);
}

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
    
    // Setup button click handlers
    if (PlayButton)
    {
        PlayButton->OnClicked().AddUObject(this, &UGameSelectionWidget::HandlePlayButtonClicked);
    }
    
    if (BackButton)
    {
        BackButton->OnClicked().AddUObject(this, &UGameSelectionWidget::HandleBackButtonClicked);
    }
    
    // Initialize the tile view
    InitializeGameTileView();
    
    // Select the first game
    if (AvailableGames.Num() > 0)
    {
        SelectGame(CurrentIndex);
    }
}

void UGameSelectionWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    
    // Bind input events when activated
    BindInputEvents();
    
    // Set initial focus when activated
    if (GameTileView && GameTileView->GetNumItems() > 0)
    {
        GameTileView->SetSelectedIndex(CurrentIndex);
        GameTileView->RequestRefresh();
        
        // Set keyboard focus to the selected item
        if (UCommonButtonBase* SelectedButton = Cast<UCommonButtonBase>(GameTileView->GetItemAt(CurrentIndex)))
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

void UGameSelectionWidget::BindInputEvents()
{
    // Register with the input subsystem for navigation events
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
        // Add input handlers for navigation
        InputSubsystem->AddNavigationHandler(FCommonNavigationDelegate::CreateUObject(this, &UGameSelectionWidget::HandlePlayButtonClicked), 
            ECommonInputType::Gamepad, ECommonInputMode::Menu, FName("UI_Accept"));
        
        InputSubsystem->AddNavigationHandler(FCommonNavigationDelegate::CreateUObject(this, &UGameSelectionWidget::HandleBackButtonClicked), 
            ECommonInputType::Gamepad, ECommonInputMode::Menu, FName("UI_Back"));
    }
}

void UGameSelectionWidget::UnbindInputEvents()
{
    // Unregister from the input subsystem
    if (UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
    {
        InputSubsystem->RemoveAllNavigationHandlers(this);
    }
}

void UGameSelectionWidget::InitializeGameTileView()
{
    if (!GameTileView)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("GameTileView is not set in GameSelectionWidget"));
        return;
    }
    
    // Clear existing items
    GameTileView->ClearListItems();
    
    // Add game cards for each available game
    for (int32 i = 0; i < AvailableGames.Num(); ++i)
    {
        UGameCardWidget* GameCard = CreateWidget<UGameCardWidget>(this, GameTileView->GetEntryWidgetClass());
        if (GameCard)
        {
            GameCard->SetGameType(AvailableGames[i]);
            GameTileView->AddItem(GameCard);
        }
    }
    
    // Set up tile view selection event
    GameTileView->OnItemSelectionChanged().AddUObject(this, &UGameSelectionWidget::HandleGameCardClicked);
}

void UGameSelectionWidget::HandleGameCardClicked(UObject* Item)
{
    UGameCardWidget* GameCard = Cast<UGameCardWidget>(Item);
    if (GameCard)
    {
        // Find the index of the selected game
        EGameType SelectedType = GameCard->GetGameType();
        for (int32 i = 0; i < AvailableGames.Num(); ++i)
        {
            if (AvailableGames[i] == SelectedType)
            {
                SelectGame(i);
                break;
            }
        }
    }
}

void UGameSelectionWidget::HandlePlayButtonClicked()
{
    PlaySelectedGame();
}

void UGameSelectionWidget::HandleBackButtonClicked()
{
    ReturnToMainMenu();
}

void UGameSelectionWidget::SelectGame(int32 GameIndex)
{
    if (GameIndex < 0 || GameIndex >= AvailableGames.Num())
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Invalid game index: %d"), GameIndex);
        return;
    }
    
    CurrentIndex = GameIndex;
    const EGameType GameType = AvailableGames[GameIndex];
    
    if (GameType == EGameType::None)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Invalid game type at index %d"), GameIndex);
        return;
    }
    
    SelectedGameType = GameType;
    
    // Update the tile view selection
    if (GameTileView)
    {
        GameTileView->SetSelectedIndex(GameIndex);
    }
    
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
    DeactivateWidget();
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
    VisibleIndices.Reserve(NumToShow);
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
    VisibleGames.Reserve(VisibleIndices.Num());
    
    for (int32 Index : VisibleIndices)
    {
        VisibleGames.Add(AvailableGames[Index]);
    }
    
    return VisibleGames;
}