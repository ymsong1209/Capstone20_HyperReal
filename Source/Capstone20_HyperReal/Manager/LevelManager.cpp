// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "../CapStoneGameInstance.h"
#include "../Building/Building.h"

ULevelManager::ULevelManager()
{
	curlevel = 1;
	mainBuildingCurHP = -1;
	mainBuildingMaxHP = -1;
	isLevelClear = false;
}

ULevelManager::~ULevelManager()
{
}

void ULevelManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Init();
}

void ULevelManager::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelManager::Init()
{
}

void ULevelManager::LoadInGameLevel()
{
	FString LevelName = FString::Printf(TEXT("Level%d"), curlevel);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
	isLevelClear = false;
}

int32 ULevelManager::GetBuildingHP()
{
	if(mainBuildingCurHP > -1)
	{
		return mainBuildingCurHP;
	}
	else
	{
		UCapStoneGameInstance* gameInstance = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
		if (!gameInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("No GameInstance"));
			return -1;
		}
		FString BuildingName = FString::Printf(TEXT("Tower%d"), curlevel);
		const FBuildingDataTableInfo* table = gameInstance->FindBuildingInfo(BuildingName);
		if (!table)
		{
			UE_LOG(LogTemp, Error, TEXT("No BuildingInfoTable"));
			return -1;
		}
		mainBuildingCurHP = table->HP;
		mainBuildingMaxHP = table->HP;
		return mainBuildingCurHP;
	}
}

int32 ULevelManager::GetBuildingMaxHP()
{
	if(mainBuildingMaxHP > -1)
	{
		return mainBuildingMaxHP;
	}
	else
	{
		UCapStoneGameInstance* gameInstance = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
		if (!gameInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("No GameInstance"));
			return -1;
		}
		FString BuildingName = FString::Printf(TEXT("Tower%d"), curlevel);
		const FBuildingDataTableInfo* table = gameInstance->FindBuildingInfo(BuildingName);
		if (!table)
		{
			UE_LOG(LogTemp, Error, TEXT("No BuildingInfoTable"));
			return -1;
		}
		mainBuildingCurHP = table->HP;
		mainBuildingMaxHP = table->HP;
		return mainBuildingMaxHP;
	}
}

void ULevelManager::LevelClear()
{
	isLevelClear = true;
	curlevel++;
	mainBuildingCurHP = -1;
	mainBuildingMaxHP = -1;
}
