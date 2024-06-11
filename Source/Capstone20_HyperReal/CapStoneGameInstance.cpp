// Fill out your copyright notice in the Description page of Project Settings.


#include "CapStoneGameInstance.h"
#include "Manager/PlayerManager.h"
#include "Manager/RuneManager.h"

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

void UCapStoneGameInstance::UpgradePlayerStat(EPlayerUpgradeType _eType)
{
	m_PlayerManager->UpgradePlayerStat(_eType);
}

void UCapStoneGameInstance::UpgradeRune(ERuneType _eType)
{
	m_RuneManager->UpgradeRune(_eType);
}

void UCapStoneGameInstance::UpgradeHealth()
{
	m_PlayerManager->RestoreHealth();
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
		if(!table)
		{
			UE_LOG(LogTemp, Error, TEXT("No PlayerInfoTable"));
			return;
		}
		table->TotalGold += _gold;
		UE_LOG(LogTemp, Log, TEXT("Player Gold : %d"), table->TotalGold);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No PlayerInfoTable"));
	}
}

void UCapStoneGameInstance::Init()
{
	Super::Init();

	// 만약 저장데이터가 있었다면 다른 처리를 통해 스탯 정보를 불러와야함
	m_PlayerManager = GetSubsystem<UPlayerManager>();

	if (m_PlayerManager)
		m_PlayerManager->Init(TEXT("Soldier"));

	m_RuneManager = GetSubsystem<URuneManager>();
}
