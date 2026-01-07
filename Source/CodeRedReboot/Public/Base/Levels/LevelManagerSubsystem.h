// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "Base/Data/GameInformationStructs.h"
#include "LevelManagerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataTableLoaded);

struct FStreamableHandle;

UCLASS(Config = Game)
class CODEREDREBOOT_API ULevelManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Public getter for the data table
	UDataTable* GetLevelDataTable() const { return LevelDataTable.Get(); }

	// Event to broadcast when the data table is loaded
	UPROPERTY(BlueprintAssignable, Category = "Level Loading")
	FOnDataTableLoaded OnDataTableLoaded;

	void LoadGameLevels(const TArray<FPrimaryAssetId> LevelAssetIds);
	void LoadGameLevel(FPrimaryAssetId LevelId);
private:
	void PerformLoad(FPrimaryAssetId LevelId);
	void OpenNewMap(const FSoftObjectPath& LevelPath);
	void StreamLevel(const FSoftObjectPath& LevelPath, bool bMakeVisibleAfterLoad, bool bShouldblockOnLoad, const FLatentActionInfo& LatentInfo);
	void LoadWorldPartitionLevel(const FSoftObjectPath& LevelPath, const TArray<FName>& DataLayers);

	UPROPERTY(Config)
	FSoftObjectPath LevelDataTablePath;

	UPROPERTY()
	TSoftObjectPtr<UDataTable> LevelDataTable;

	TSharedPtr<FStreamableHandle> DataTableHandle;
	
	UFUNCTION()
	void OnLevelDataTableLoaded();
};
