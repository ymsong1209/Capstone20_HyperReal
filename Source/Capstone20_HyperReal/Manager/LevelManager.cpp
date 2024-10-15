// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "../CapStoneGameInstance.h"
#include "../Building/Building.h"
#include "../Save/LevelSaveGame.h"

ULevelManager::ULevelManager()
{
	curlevel = 1;
	mainBuilding = nullptr;
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

void ULevelManager::SaveLevelData(USaveGame* _pSaveGame)
{
	ULevelSaveGame* saveGame = Cast<ULevelSaveGame>(_pSaveGame);
	if(!saveGame)
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame is Null"));
		return;
	}
	saveGame->curlevel = curlevel;
	saveGame->mainBuildingCurHP = mainBuildingCurHP;
	saveGame->mainBuildingMaxHP = mainBuildingMaxHP;
}

void ULevelManager::LoadLevelData(USaveGame* _pSaveGame)
{
	ULevelSaveGame* saveGame = Cast<ULevelSaveGame>(_pSaveGame);
	if(!saveGame)
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame is Null"));
		return;
	}
	curlevel = saveGame->curlevel;
	mainBuildingCurHP = saveGame->mainBuildingCurHP;
	mainBuildingMaxHP = saveGame->mainBuildingMaxHP;
	UE_LOG(LogTemp, Log, TEXT("curlevel : %d"), curlevel);
	UE_LOG(LogTemp, Log, TEXT("mainBuildingCurHP : %d"), mainBuildingCurHP);
	UE_LOG(LogTemp, Log, TEXT("mainBuildingMaxHP : %d"), mainBuildingMaxHP);
	UE_LOG(LogTemp, Log, TEXT("LevelData Load Success"));
}


void ULevelManager::LoadInGameLevel()
{
	// FString LevelName = FString::Printf(TEXT("Level%d"), curlevel);
	// UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
	FString LevelName = FString::Printf(TEXT("/Game/Maps/Level%d"), curlevel);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
	isLevelClear = false;
	mainBuilding = nullptr;
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

void ULevelManager::SetBuildingHP()
{
	if(!mainBuilding) return;
	mainBuildingCurHP = FMath::Clamp(mainBuildingCurHP,-1,mainBuilding->GetBuildingInfo().HP);
	mainBuildingMaxHP = FMath::Clamp(mainBuildingMaxHP,-1,mainBuilding->GetBuildingInfo().MaxHP);
}

void ULevelManager::LevelClear()
{
	isLevelClear = true;
	mainBuilding = nullptr;
	curlevel++;
	mainBuildingCurHP = -1;
	mainBuildingMaxHP = -1;
}
