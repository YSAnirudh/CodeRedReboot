// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Base/Data/GameInformationStructs.h"
#include "Carousel.generated.h"

class UHorizontalBox;
class UGameCardWidget;
class UGameInformationObject;

/**
 * 
 */
UCLASS()
class CODEREDREBOOT_API UCarousel : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	
public:

	UCarousel();

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	UFUNCTION(BlueprintCallable)
	void ShiftLeft();

	UFUNCTION(BlueprintCallable)
	void ShiftRight();

	UFUNCTION()
	void OnShiftLeftAnimFinish();

	UFUNCTION()
	void OnShiftRightAnimFinish();

	UFUNCTION()
	void OnShiftLeftAnimStart();

	UFUNCTION()
	void OnShiftRightAnimStart();

	UGameCardWidget* GetSelectedGame() const { return CenterCard; }

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameInformation")
	TArray<FGameInformation> GameList;

	int CurrentIndex = 0;

private:

	void HideCards() const;
	void SetCardsPerPlace() const;
	void SetCenterCardActive(bool bActive) const;

private:

	bool bIsInAnim = false;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidget))
	UGameCardWidget* BackCard = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidget))
	UGameCardWidget* LeftCard = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidget))
	UGameCardWidget* RightCard = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidget))
	UGameCardWidget* CenterCard = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidgetAnim))
	UWidgetAnimation* ShiftLeftAnim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidgetAnim))
	UWidgetAnimation* ShiftRightAnim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidgetAnim))
	UWidgetAnimation* ShiftLeftStuckAnim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidgetAnim))
	UWidgetAnimation* ShiftRightStuckAnim = nullptr;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category = "Carousel", meta = (BindWidgetAnim))
	UWidgetAnimation* ResetCardsAnim = nullptr;

};
