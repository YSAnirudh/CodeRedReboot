// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base/Character/BasePawnInterface.h"
#include "Base/AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CODEREDREBOOT_API ABaseCharacter : public ACharacter, public IBasePawnInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UBaseAbilitySystemComponent* GetBaseAbilitySystem_Implementation() const override;
	virtual void OnGameSwitched_Implementation(EGameType GameType) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UBaseAbilitySystemComponent* AbilitySystemComponent = nullptr;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UBaseAttributeSet* AttributeSet;*/

	virtual void InitializeAbilities();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
