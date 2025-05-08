// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/GameSettings/BaseGameMode.h"
#include "HubGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API AHubGameMode : public ABaseGameMode
{
	GENERATED_BODY()
	
public:
	AHubGameMode();

	virtual void BeginPlay() override;

	void InitializeHubSystems();

	UFUNCTION(BlueprintCallable, Category = "Hub")
	void OnPlayerEnteredHub(APlayerController* PlayerController);
};
