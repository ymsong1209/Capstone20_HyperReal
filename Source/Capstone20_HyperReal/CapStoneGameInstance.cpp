// Fill out your copyright notice in the Description page of Project Settings.


#include "CapStoneGameInstance.h"


UCapStoneGameInstance::UCapStoneGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterTableAsset(TEXT("/Script/Engine.DataTable'/Game/A_SYMContent/Monster/DT_MonsterInfo.DT_MonsterInfo'"));
	if (MonsterTableAsset.Succeeded()) {
		mMonsterInfoTable = MonsterTableAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingTableAsset(TEXT("/Script/Engine.DataTable'/Game/A_SYMContent/Building/DT_BuildingInfo.DT_BuildingInfo'"));
	if (BuildingTableAsset.Succeeded()) {
		mBuildingInfoTable = BuildingTableAsset.Object;
	}
	
	//static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTableAsset(TEXT(""));
	//if (PlayerTableAsset.Succeeded()) {
	//	mPlayerInfoTable = PlayerTableAsset.Object;
	//}
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTableAsset(TEXT("/Script/Engine.DataTable'/Game/A_KHIContent/DataTable/PlayerDT.PlayerDT'"));
	if (PlayerTableAsset.Succeeded()) {
		mPlayerInfoTable = PlayerTableAsset.Object;
	}
}

const FMonsterDataTableInfo* UCapStoneGameInstance::FindMonsterInfo(const FString& _Name)
{
	if (mMonsterInfoTable) {
		return mMonsterInfoTable->FindRow<FMonsterDataTableInfo>(*_Name, TEXT(""));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No MonsterInfoTable"));
		return nullptr;
	}
}

const FPlayerDataTableInfo* UCapStoneGameInstance::FindPlayerInfo(const FString& _Name)
{
	if (mPlayerInfoTable) {
		return mPlayerInfoTable->FindRow<FPlayerDataTableInfo>(*_Name, TEXT(""));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No PlayerInfoTable"));
		return nullptr;
	}
	
}

const FBuildingDataTableInfo* UCapStoneGameInstance::FindBuildingInfo(const FString& _Name)
{
	if (mBuildingInfoTable) {
		return mBuildingInfoTable->FindRow<FBuildingDataTableInfo>(*_Name, TEXT(""));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No BuildingInfoTable"));
		return nullptr;
	}
}

void UCapStoneGameInstance::UpdatePlayerGold(const FString& PlayerName, int _gold)
{
	if (mPlayerInfoTable) {
		FPlayerDataTableInfo* table =  mPlayerInfoTable->FindRow<FPlayerDataTableInfo>(*PlayerName, TEXT(""));
		table->TotalGold += _gold;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No PlayerInfoTable"));
	}
}

void UCapStoneGameInstance::Init()
{
}
