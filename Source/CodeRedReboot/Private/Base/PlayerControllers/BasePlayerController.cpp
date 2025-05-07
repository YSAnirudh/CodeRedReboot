// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PlayerControllers/BasePlayerController.h"
#include "Base/Input/BaseInputComponent.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseLogChannels.h"
#include "Base/Character/BasePawnInterface.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UBaseInputComponent* EnhancedInputComponent = Cast<UBaseInputComponent>(InputComponent))
	{
		if (InputMappingContext)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			if (Subsystem)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
			else
			{
				UE_LOG(LogBaseInput, Error, TEXT("No Enhanced Input Local Player Subsystem found!"));
			}
		}
		else
		{
			UE_LOG(LogBaseInput, Warning, TEXT("Input mapping passed into the player controller %s is null"), *GetName());
		}

		if (InputConfig)
		{
			TArray<uint32> BindHandles;
			EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ABasePlayerController::Input_AbilityInputTagPressed, &ABasePlayerController::Input_AbilityInputTagReleased, BindHandles);
		}
		else
		{
			UE_LOG(LogBaseInput, Warning, TEXT("Input config passed into the player controller %s is null"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogBaseInput, Error, TEXT("No Enhanced Input Component found!"));
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


