#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "Engine/DataTable.h"
#include "GameInformationStructs.generated.h"

UENUM(BlueprintType)
enum class EGameType : uint8
{
	None        UMETA(DisplayName = "None"),
	Hub         UMETA(DisplayName = "Hub"),
	GOW	        UMETA(DisplayName = "GOW"),
	SpiderMan   UMETA(DisplayName = "SpiderMan"),
	Control     UMETA(DisplayName = "Control"),
};

UENUM(BlueprintType)
enum ELevelStreamingType : uint8
{
	LST_FullLoad		UMETA(DisplayName = "Full Load"),
	LST_Stream			UMETA(DisplayName = "Stream"),
	LST_WorldPartition	UMETA(DisplayName = "World Partition")
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId LevelId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath LevelPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ELevelStreamingType> LevelStreamingType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> DataLayersToLoad;

};

USTRUCT(BlueprintType, Blueprintable)
struct FGameInformation : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information")
	EGameType GameType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information")
	FString GameName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information")
	FString GameDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information")
	UImage* GameThumbnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Information")
	TMap<FString, FPrimaryAssetId> LevelDataMap;
};