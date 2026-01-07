// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "Base/Data/GameInformationStructs.h"
#include "GameInformationObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CODEREDREBOOT_API UGameInformationObject : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information", meta = (ExposeOnSpawn = "true"))
	FGameInformation GameInfo;
};
