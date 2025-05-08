// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/BaseCharacter.h"
#include "BaseLogChannels.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UBaseAbilitySystemComponent* ABaseCharacter::GetBaseAbilitySystem_Implementation() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::OnGameSwitched_Implementation(EGameType NewGameType)
{
	UE_LOG(LogBaseCharacter, Log, TEXT("Character %s switched to game type: %s"), *GetName(), *UEnum::GetValueAsString(NewGameType));
}

void ABaseCharacter::InitializeAbilities()
{
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

