#include "Base/UI/GameCardWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UGameCardWidget::SetGameType(EGameType InGameType)
{
    GameType = InGameType;
    UpdateGameInfo();
}

void UGameCardWidget::SetSelected(bool bIsSelected)
{
    bSelected = bIsSelected;
    OnSelected(bIsSelected);
}