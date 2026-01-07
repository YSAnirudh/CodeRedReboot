// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Levels/LevelManagerSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "BaseLogChannels.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/WorldPartitionSubsystem.h"

void ULevelManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (!LevelDataTablePath.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LevelDataTablePath is not set in DefaultGame.ini!"));
        return;
    }

    // Get the FStreamableManager from the AssetManager
    FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();

    // Request async load using the soft object path
    DataTableHandle = StreamableManager.RequestAsyncLoad(
        LevelDataTablePath,
        FStreamableDelegate::CreateUObject(this, &ULevelManagerSubsystem::OnLevelDataTableLoaded)
    );
}

void ULevelManagerSubsystem::Deinitialize()
{
    Super::Deinitialize();

    if (DataTableHandle.IsValid())
    {
        DataTableHandle->CancelHandle();
        DataTableHandle.Reset();
    }
    LevelDataTable.Reset();
}

void ULevelManagerSubsystem::LoadGameLevels(const TArray<FPrimaryAssetId> LevelAssetIds)
{
    if (LevelDataTable.IsValid())
    {
        for (FPrimaryAssetId LevelId : LevelAssetIds)
        {
            PerformLoad(LevelId);
        }
    }
    else
    {
        UE_LOG(LogLevelLoading, Warning, TEXT("Cannot Load Level Data table: %s"), *LevelDataTable.Get()->GetName())
            //// Data table not loaded yet, bind to the delegate
            //FOnDataTableLoaded::FDelegate Delegate;
            //Delegate.(
            //    this,
            //    &ULevelManagerSubsystem::PerformLoad,
            //    LevelId
            //);
            //OnDataTableLoaded.AddUnique(Delegate);
    }
}

void ULevelManagerSubsystem::LoadGameLevel(FPrimaryAssetId LevelId)
{
    if (LevelDataTable.IsValid())
    {
        PerformLoad(LevelId);
    }
    else
    {
        UE_LOG(LogLevelLoading, Warning, TEXT("Cannot Load Level Data table: %s"), *LevelDataTable.Get()->GetName())
        //// Data table not loaded yet, bind to the delegate
        //FOnDataTableLoaded::FDelegate Delegate;
        //Delegate.(
        //    this,
        //    &ULevelManagerSubsystem::PerformLoad,
        //    LevelId
        //);
        //OnDataTableLoaded.AddUnique(Delegate);
    }
}

void ULevelManagerSubsystem::PerformLoad(FPrimaryAssetId LevelId)
{
    if (LevelDataTable == nullptr || !LevelDataTable.IsValid())
    {
        return;
    }

    if (FLevelData* LevelData = LevelDataTable->FindRow<FLevelData>(LevelId.PrimaryAssetName, TEXT("LevelDataLookup")))
    {
        switch (LevelData->LevelStreamingType)
        {
        case ELevelStreamingType::LST_FullLoad:
            OpenNewMap(LevelData->LevelPath);
            break;
        case ELevelStreamingType::LST_Stream:
            StreamLevel(LevelData->LevelPath, true, true, FLatentActionInfo());
            break;
        case ELevelStreamingType::LST_WorldPartition:
            LoadWorldPartitionLevel(LevelData->LevelPath, LevelData->DataLayersToLoad);
            break;
        }
    }
}

void ULevelManagerSubsystem::OpenNewMap(const FSoftObjectPath& LevelPath)
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(LevelPath.GetLongPackageName()));
}

void ULevelManagerSubsystem::StreamLevel(const FSoftObjectPath& LevelPath, bool bMakeVisibleAfterLoad, bool bShouldblockOnLoad, const FLatentActionInfo& LatentInfo)
{
    // The persistent level must already be loaded
    UGameplayStatics::LoadStreamLevel(GetWorld(), FName(LevelPath.GetLongPackageName()), bMakeVisibleAfterLoad, bShouldblockOnLoad, LatentInfo);
}

void ULevelManagerSubsystem::LoadWorldPartitionLevel(const FSoftObjectPath& LevelPath, const TArray<FName>& DataLayers)
{
    OpenNewMap(LevelPath); // Open the World Partition map

    // TODO: Data Layers need to be handled separately
}

void ULevelManagerSubsystem::OnLevelDataTableLoaded()
{
    if (DataTableHandle.IsValid())
    {
        // Get the loaded object from the handle
        LevelDataTable = Cast<UDataTable>(DataTableHandle->GetLoadedAsset());

        if (LevelDataTable.IsValid())
        {
            UE_LOG(LogLevelLoading, Log, TEXT("Asynchronously loaded Level Data Table!"));
            OnDataTableLoaded.Broadcast();
        }
        else
        {
            UE_LOG(LogLevelLoading, Error, TEXT("Failed to asynchronously load Level Data Table!"));
        }

        // Release the handle once loading is complete and we have a hard pointer
        DataTableHandle.Reset();
    }
}
