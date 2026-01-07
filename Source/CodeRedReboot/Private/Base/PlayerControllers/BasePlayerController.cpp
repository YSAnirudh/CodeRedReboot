// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PlayerControllers/BasePlayerController.h"
#include "Base/Input/BaseInputComponent.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseLogChannels.h"
#include "BaseGameplayTags.h"
#include "Base/Character/BasePawnInterface.h"
#include "Base/GameSettings/MultiGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UMultiGameInstance* GameInstance = Cast<UMultiGameInstance>(GetGameInstance()))
	{
		GameInstance->OnGameTypeChanged.AddDynamic(this, &ABasePlayerController::OnGameTypeChanged);
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UMultiGameInstance* GameInstance = Cast<UMultiGameInstance>(GetGameInstance()))
	{
		UpdateInputMappingContext(GameInstance->GetCurrentGameType());
	}

	if (InputConfig)
	{
		TArray<uint32> BindHandles;
		if (UBaseInputComponent* EnhancedInputComponent = Cast<UBaseInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ABasePlayerController::Input_AbilityInputTagPressed, &ABasePlayerController::Input_AbilityInputTagReleased, BindHandles);

			//EnhancedInputComponent->BindNativeAction(InputConfig, )
		}
	}
	else
	{
		UE_LOG(LogBaseInput, Warning, TEXT("Input config passed into the player controller %s is null"), *GetName());
	}
}

// This function is called when the player presses an ability input tag
void ABasePlayerController::Input_AbilityInputTagPressed(FGameplayTag AbilityInputTag)
{
	if (IBasePawnInterface* PawnInterface = Cast<IBasePawnInterface>(GetPawn()))
	{
		if (UBaseAbilitySystemComponent* AbilitySystem = PawnInterface->GetBaseAbilitySystem())
		{
			if (AbilitySystem)
			{
				AbilitySystem->AbilityInputTagPressed(AbilityInputTag);
			}
			else
			{
				UE_LOG(LogBaseInput, Warning, TEXT("No Ability System found on pawn %s"), *GetPawn()->GetName());
			}
		}
		else
		{
			UE_LOG(LogBaseInput, Warning, TEXT("Pawn %s does not implement IBasePawnInterface"), *GetPawn()->GetName());
		}
	}
}

// This function is called when the player releases an ability input tag
void ABasePlayerController::Input_AbilityInputTagReleased(FGameplayTag AbilityInputTag)
{
	if (IBasePawnInterface* PawnInterface = Cast<IBasePawnInterface>(GetPawn()))
	{
		if (UBaseAbilitySystemComponent* AbilitySystem = PawnInterface->GetBaseAbilitySystem())
		{
			if (AbilitySystem)
			{
				AbilitySystem->AbilityInputTagReleased(AbilityInputTag);
			}
			else
			{
				UE_LOG(LogBaseInput, Warning, TEXT("No Ability System found on pawn %s"), *GetPawn()->GetName());
			}
		}
		else
		{
			UE_LOG(LogBaseInput, Warning, TEXT("Pawn %s does not implement IBasePawnInterface"), *GetPawn()->GetName());
		}
	}
}

void ABasePlayerController::SwitchGame(EGameType NewGameType)
{
	UMultiGameInstance* GameInstance = Cast<UMultiGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogBaseInput, Error, TEXT("No MultiGameInstance found!"));
		return;
	}

	const EGameType CurrentGameType = GameInstance->GetCurrentGameType();

	if (CurrentGameType != EGameType::Hub && NewGameType != EGameType::Hub)
	{
		UE_LOG(LogBaseInput, Error, TEXT("Cannot switch between games. Trying to switch to %s from %s."),
			*UEnum::GetValueAsString(NewGameType),
			*UEnum::GetValueAsString(CurrentGameType)
		);
		return;
	}

	if (GameInstance->GetCurrentGameType() == NewGameType)
	{
		UE_LOG(LogBaseInput, Warning, TEXT("Already in the requested game type: %s"), *UEnum::GetValueAsString(NewGameType));
		return;
	}

	// Need Async Loading Screen that Tracks when a level is loaded.
	ShowLoadingScreen();

	GameInstance->SaveGameState();

	GameInstance->SwitchGame(NewGameType);

	UE_LOG(LogBasePlayerController, Log, TEXT("Switching to game: %s"), *UEnum::GetValueAsString(NewGameType));
}

void ABasePlayerController::ReturnToHub()
{
	SwitchGame(EGameType::Hub);
}

void ABasePlayerController::OnGameTypeChanged(EGameType PreviousGameType, EGameType NewGameType)
{
	UpdateInputMappingContext(NewGameType);

	if (GetPawn())
	{
		if (IBasePawnInterface* PawnInterface = Cast<IBasePawnInterface>(GetPawn()))
		{
			if (UBaseAbilitySystemComponent* AbilitySystem = PawnInterface->GetBaseAbilitySystem())
			{
				if (AbilitySystem)
				{
					AbilitySystem->ClearAbilityInput();
				}
			}

			PawnInterface->OnGameSwitched(NewGameType);
		}
	}
}

void ABasePlayerController::ShowLoadingScreen()
{
	if (LoadingScreenClass)
	{
		if (LoadingScreenWidget == nullptr)
		{
			LoadingScreenWidget = CreateWidget<UUserWidget>(this, LoadingScreenClass);
			if (LoadingScreenWidget)
			{
				LoadingScreenWidget->AddToViewport();
			}
		}
	}
	else
	{
		UE_LOG(LogBaseInput, Error, TEXT("No Loading Screen Class set in the player controller %s"), *GetName());
	}
}

void ABasePlayerController::HideLoadingScreen()
{
	if (LoadingScreenWidget)
	{
		LoadingScreenWidget->RemoveFromParent();
		LoadingScreenWidget = nullptr;
	}
	else
	{
		UE_LOG(LogBaseInput, Warning, TEXT("No Loading Screen Widget found in the player controller %s"), *GetName());
	}
}

void ABasePlayerController::OnLevelLoadComplete()
{
	UMultiGameInstance* GameInstance = Cast<UMultiGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->LoadGameState();

		HideLoadingScreen();
	}
}

void ABasePlayerController::UpdateInputMappingContext(EGameType GameType)
{
	if (UBaseInputComponent* EnhancedInputComponent = Cast<UBaseInputComponent>(InputComponent))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (Subsystem)
		{
			Subsystem->ClearAllMappings();

			if (GameInputMappingContexts.Contains(GameType))
			{
				UInputMappingContext* InputMappingContext = GameInputMappingContexts[GameType];
				if (InputMappingContext)
				{
					Subsystem->AddMappingContext(InputMappingContext, 0);
					UE_LOG(LogBaseInput, Log, TEXT("Updated Input Mapping Context for game type %s"), *UEnum::GetValueAsString(GameType));
				}
			}
			else
			{
				UE_LOG(LogBaseInput, Warning, TEXT("No Input Mapping Context found for game type %s"), *UEnum::GetValueAsString(GameType));
			}
		}
		else
		{
			UE_LOG(LogBaseInput, Error, TEXT("No Enhanced Input Local Player Subsystem found!"));
		}
	}
	else
	{
		UE_LOG(LogBaseInput, Error, TEXT("No Enhanced Input Component found!"));
	}
}

void ABasePlayerController::PostProcessInput(float DeltaTime, bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (IBasePawnInterface* PawnInterface = Cast<IBasePawnInterface>(GetPawn()))
	{
		if (UBaseAbilitySystemComponent* AbilitySystem = PawnInterface->GetBaseAbilitySystem())
		{
			if (AbilitySystem)
			{
				AbilitySystem->ProcessAbilityInput(0.f, false);
			}
		}
	}
}


