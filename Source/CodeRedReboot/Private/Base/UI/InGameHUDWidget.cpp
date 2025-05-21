#include "Base/UI/InGameHUDWidget.h"
#include "Base/PlayerControllers/BasePlayerController.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "BaseLogChannels.h"

void UInGameHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (ReturnToHubButton)
    {
        ReturnToHubButton->OnClicked.AddDynamic(this, &UInGameHUDWidget::OnReturnToHubClicked);
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

void UInGameHUDWidget::OnReturnToHubClicked()
{
    ReturnToHub();
}