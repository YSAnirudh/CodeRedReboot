// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UI/Carousel/Carousel.h"
#include "Base/UI/GameCardWidget.h"
#include "Components/HorizontalBox.h"
#include "BaseLogChannels.h"
#include "Animation/WidgetAnimation.h"

UCarousel::UCarousel()
{
}

void UCarousel::NativeConstruct()
{
	if (UMultiGameInstance* MultiGameInstance = Cast<UMultiGameInstance>(GetGameInstance()))
	{
		TArray<FGameInformation> GameListCollect = MultiGameInstance->GetGameInformationList();

		// Empty list table for population;
		GameList.Empty();
		int32 Index = 0;
		for (FGameInformation GameInfo : GameListCollect)
		{
			UE_LOG(LogTemp, Warning, TEXT("Game Name: %s"), *GameInfo.GameName);
			GameList.Add(GameInfo);
			Index++;
		}

		SetCardsPerPlace();
		SetCenterCardActive(true);
	}

	Super::NativeConstruct();
}

void UCarousel::NativeOnActivated()
{
	Super::NativeOnActivated();

	FWidgetAnimationDynamicEvent LeftAnimFinishedEvent;
	LeftAnimFinishedEvent.BindDynamic(this, &UCarousel::OnShiftLeftAnimFinish);
	BindToAnimationFinished(ShiftLeftAnim, LeftAnimFinishedEvent);

	FWidgetAnimationDynamicEvent LeftAnimStartedEvent;
	LeftAnimStartedEvent.BindDynamic(this, &UCarousel::OnShiftLeftAnimStart);
	BindToAnimationStarted(ShiftLeftAnim, LeftAnimStartedEvent);

	FWidgetAnimationDynamicEvent RightAnimFinishedEvent;
	RightAnimFinishedEvent.BindDynamic(this, &UCarousel::OnShiftRightAnimFinish);
	BindToAnimationFinished(ShiftRightAnim, RightAnimFinishedEvent);

	FWidgetAnimationDynamicEvent RightAnimStartedEvent;
	RightAnimStartedEvent.BindDynamic(this, &UCarousel::OnShiftRightAnimStart);
	BindToAnimationStarted(ShiftRightAnim, RightAnimStartedEvent);
}

void UCarousel::ShiftLeft()
{
	if (bIsInAnim)
	{
		return;
	}

	if (GameList.Num() == 0)
	{
		HideCards();
		return;
	}

	if (GameList.Num() == 1)
	{
		StopAllAnimations();
		PlayAnimationForward(ShiftLeftStuckAnim);
		return;
	}

	// Center -> Current
	// Left -> Current - 1
	// Right -> Current + 1
	// Back -> Current + 2

	if (GameList.Num() >= 3)
	{
		const int CenterIndex = CurrentIndex == 0 ? GameList.Num() - 1 : CurrentIndex - 1;
		const int RightIndex = CurrentIndex;
		const int BackIndex = (CurrentIndex + 1) % GameList.Num();

		int LeftIndex = 0;
		if (CurrentIndex <= 1)
		{
			if (CurrentIndex == 0)
			{
				LeftIndex = GameList.Num() - 2;
			}
			else
			{
				LeftIndex = GameList.Num() - 1;
			}
		}
		else
		{
			LeftIndex = CurrentIndex - 2;
		}

		UE_LOG(LogTemp, Warning, TEXT("Right: %d | Left: %d | Back: %d"), RightIndex, LeftIndex, BackIndex);

		CenterCard->SetVisibility(ESlateVisibility::Visible);
		CenterCard->SetGameInfo(GameList[CenterIndex]);

		RightCard->SetVisibility(ESlateVisibility::Visible);
		RightCard->SetGameInfo(GameList[RightIndex]);

		LeftCard->SetVisibility(ESlateVisibility::Visible);
		LeftCard->SetGameInfo(GameList[LeftIndex]);

		BackCard->SetVisibility(ESlateVisibility::Visible);
		BackCard->SetGameInfo(GameList[BackIndex]);
	}
	else
	{
		if (CurrentIndex == 0)
		{
			LeftCard->SetVisibility(ESlateVisibility::Hidden);
			BackCard->SetVisibility(ESlateVisibility::Hidden);

			CenterCard->SetVisibility(ESlateVisibility::Visible);
			CenterCard->SetGameInfo(GameList[CurrentIndex]);

			RightCard->SetVisibility(ESlateVisibility::Visible);
			RightCard->SetGameInfo(GameList[CurrentIndex + 1]); // 1

			StopAllAnimations();
			PlayAnimationForward(ShiftLeftStuckAnim);
			return;
		}
		else
		{
			LeftCard->SetVisibility(ESlateVisibility::Hidden);
			BackCard->SetVisibility(ESlateVisibility::Hidden);

			CenterCard->SetVisibility(ESlateVisibility::Visible);
			CenterCard->SetGameInfo(GameList[CurrentIndex - 1]); // 0

			RightCard->SetVisibility(ESlateVisibility::Visible);
			RightCard->SetGameInfo(GameList[CurrentIndex]);
		}
	}

	CurrentIndex = CurrentIndex == 0 ? GameList.Num() - 1 : CurrentIndex - 1;
	StopAllAnimations();
	SetCenterCardActive(false);
	PlayAnimationForward(ShiftLeftAnim);
}

void UCarousel::ShiftRight()
{
	if (bIsInAnim)
	{
		return;
	}

	if (GameList.Num() == 0)
	{
		HideCards();
		return;
	}

	if (GameList.Num() == 1)
	{
		StopAllAnimations();
		PlayAnimationForward(ShiftRightStuckAnim);
		return;
	}

	if (GameList.Num() >= 3)
	{
		const int CenterIndex = CurrentIndex;
		const int RightIndex = (CurrentIndex + 1) % GameList.Num();
		const int LeftIndex = CurrentIndex == 0 ? GameList.Num() - 1 : CurrentIndex - 1;
		const int BackIndex = (CurrentIndex + 2) % GameList.Num();

		UE_LOG(LogTemp, Warning, TEXT("Right: %d | Left: %d | Back: %d"), RightIndex, LeftIndex, BackIndex);

		RightCard->SetVisibility(ESlateVisibility::Visible);
		CenterCard->SetGameInfo(GameList[CenterIndex]);

		RightCard->SetVisibility(ESlateVisibility::Visible);
		RightCard->SetGameInfo(GameList[RightIndex]);

		LeftCard->SetVisibility(ESlateVisibility::Visible);
		LeftCard->SetGameInfo(GameList[LeftIndex]);

		BackCard->SetVisibility(ESlateVisibility::Visible);
		BackCard->SetGameInfo(GameList[BackIndex]);
	}
	else
	{
		// Num == 2
		if (CurrentIndex == 0)
		{
			BackCard->SetVisibility(ESlateVisibility::Hidden);
			RightCard->SetVisibility(ESlateVisibility::Hidden);

			RightCard->SetVisibility(ESlateVisibility::Visible);
			RightCard->SetGameInfo(GameList[CurrentIndex + 1]); // 1

			CenterCard->SetVisibility(ESlateVisibility::Visible);
			CenterCard->SetGameInfo(GameList[CurrentIndex]);
		}
		else
		{
			RightCard->SetVisibility(ESlateVisibility::Hidden);
			BackCard->SetVisibility(ESlateVisibility::Hidden);

			CenterCard->SetVisibility(ESlateVisibility::Visible);
			CenterCard->SetGameInfo(GameList[CurrentIndex]);

			LeftCard->SetVisibility(ESlateVisibility::Visible);
			LeftCard->SetGameInfo(GameList[CurrentIndex - 1]); // 0

			StopAllAnimations();
			PlayAnimationForward(ShiftRightStuckAnim);
			return;
		}
	}

	CurrentIndex = (CurrentIndex + 1) % GameList.Num();
	StopAllAnimations();
	SetCenterCardActive(false);
	PlayAnimationForward(ShiftRightAnim);
}

void UCarousel::OnShiftLeftAnimFinish()
{
	StopAllAnimations();

	SetCardsPerPlace();
	PlayAnimationForward(ResetCardsAnim);

	bIsInAnim = false;
	SetCenterCardActive(true);
}

void UCarousel::OnShiftRightAnimFinish()
{
	StopAllAnimations();

	SetCardsPerPlace();
	PlayAnimationForward(ResetCardsAnim);

	bIsInAnim = false;
	SetCenterCardActive(true);
}

void UCarousel::OnShiftLeftAnimStart()
{
	bIsInAnim = true;
}

void UCarousel::OnShiftRightAnimStart()
{
	bIsInAnim = true;
}

void UCarousel::HideCards() const
{
	CenterCard->SetVisibility(ESlateVisibility::Hidden);
	RightCard->SetVisibility(ESlateVisibility::Hidden);
	LeftCard->SetVisibility(ESlateVisibility::Hidden);
	BackCard->SetVisibility(ESlateVisibility::Hidden);
}

void UCarousel::SetCardsPerPlace() const
{
	if (GameList.Num() == 0)
	{
		HideCards();
		return;
	}

	if (GameList.Num() >= 3)
	{
		const int CenterIndex = CurrentIndex;
		const int RightIndex = (CurrentIndex + 1) % GameList.Num();
		const int LeftIndex = CurrentIndex == 0 ? GameList.Num() - 1 : CurrentIndex - 1;

		BackCard->SetVisibility(ESlateVisibility::Hidden);

		CenterCard->SetVisibility(ESlateVisibility::Visible);
		CenterCard->SetGameInfo(GameList[CurrentIndex]);

		RightCard->SetVisibility(ESlateVisibility::Visible);
		RightCard->SetGameInfo(GameList[RightIndex]);
		
		LeftCard->SetVisibility(ESlateVisibility::Visible);
		LeftCard->SetGameInfo(GameList[LeftIndex]);
	}
	else
	{
		if (GameList.Num() == 1)
		{
			CenterCard->SetVisibility(ESlateVisibility::Visible);
			CenterCard->SetGameInfo(GameList[CurrentIndex]);

			RightCard->SetVisibility(ESlateVisibility::Hidden);
			LeftCard->SetVisibility(ESlateVisibility::Hidden);
			BackCard->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (CurrentIndex == 0)
			{
				const int RightIndex = (CurrentIndex + 1) % GameList.Num();

				LeftCard->SetVisibility(ESlateVisibility::Hidden);
				BackCard->SetVisibility(ESlateVisibility::Hidden);

				CenterCard->SetVisibility(ESlateVisibility::Visible);
				CenterCard->SetGameInfo(GameList[CurrentIndex]);

				RightCard->SetVisibility(ESlateVisibility::Visible);
				RightCard->SetGameInfo(GameList[RightIndex]);
			}
			else
			{
				const int LeftIndex = CurrentIndex == 0 ? GameList.Num() - 1 : CurrentIndex - 1;

				RightCard->SetVisibility(ESlateVisibility::Hidden);
				BackCard->SetVisibility(ESlateVisibility::Hidden);

				CenterCard->SetVisibility(ESlateVisibility::Visible);
				CenterCard->SetGameInfo(GameList[CurrentIndex]);

				LeftCard->SetVisibility(ESlateVisibility::Visible);
				LeftCard->SetGameInfo(GameList[LeftIndex]);
			}
		}
	}
}

void UCarousel::SetCenterCardActive(bool bActive) const
{
	CenterCard->SetIsEnabled(bActive);
	RightCard->SetIsEnabled(false);
	LeftCard->SetIsEnabled(false);
	BackCard->SetIsEnabled(false);
}
