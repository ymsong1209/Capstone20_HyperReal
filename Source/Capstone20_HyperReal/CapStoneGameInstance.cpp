// Fill out your copyright notice in the Description page of Project Settings.


#include "CapStoneGameInstance.h"
#include "Manager/PlayerManager.h"
#include "Manager/RuneManager.h"
#include "Manager/LevelManager.h"
#include "Save/PlayerUpgradeSaveGame.h"
#include "Save/LevelSaveGame.h"

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

void UCapStoneGameInstance::SaveGameData()
{
	SavePlayerData();
	SaveLevelData();
}

bool UCapStoneGameInstance::LoadGameData()
{
	if (!LoadPlayerData())
		return false;

	LoadLevelData();

	return true;
}

void UCapStoneGameInstance::SavePlayerData()
{
	UPlayerUpgradeSaveGame* pSaveInst = Cast<UPlayerUpgradeSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerUpgradeSaveGame::StaticClass()));

	if (!pSaveInst)
	{
		UE_LOG(LogTemp, Error, TEXT("Make PlayerUpgradeSaveGame Failed"));
		return;
	}

	if (m_PlayerManager)
		m_PlayerManager->SavePlayerInfo(pSaveInst);

	if (m_RuneManager)
		m_RuneManager->SaveRuneLevels(pSaveInst);

	UGameplayStatics::SaveGameToSlot(pSaveInst, TEXT("PlayerGameData"), 0);
	UE_LOG(LogTemp, Log, TEXT("PlayerGameData Save Success"));
}

bool UCapStoneGameInstance::LoadPlayerData()
{
	UPlayerUpgradeSaveGame* pLoadInst = Cast<UPlayerUpgradeSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerGameData"), 0));

	if (pLoadInst)
	{
		if (m_PlayerManager)
			m_PlayerManager->LoadPlayerInfo(pLoadInst);

		if (m_RuneManager)
			m_RuneManager->LoadRuneLevels(pLoadInst);

		return true;
	}	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameData Save Slot not exist"));
		return false;
	}
}

void UCapStoneGameInstance::SaveLevelData()
{
	ULevelSaveGame* pSaveInst = Cast<ULevelSaveGame>(UGameplayStatics::CreateSaveGameObject(ULevelSaveGame::StaticClass()));
	if(!pSaveInst)
	{
		UE_LOG(LogTemp, Error, TEXT("Make LevelSaveGame Failed"));
		return;
	}

	if(m_LevelManager)
		m_LevelManager->SaveLevelData(pSaveInst);

	UGameplayStatics::SaveGameToSlot(pSaveInst, TEXT("LevelData"), 0);
	UE_LOG(LogTemp, Log, TEXT("LevelData Save Success"));
}

void UCapStoneGameInstance::LoadLevelData()
{
	ULevelSaveGame* pLoadInst = Cast<ULevelSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LevelData"), 0));
	if(pLoadInst)
	{
		if(m_LevelManager)
			m_LevelManager->LoadLevelData(pLoadInst);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelData Save Slot not exist"));
	}
}

void UCapStoneGameInstance::DeleteSaveData()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerGameData"), 0))
	{
		UGameplayStatics::DeleteGameInSlot(TEXT("PlayerGameData"), 0);
		UE_LOG(LogTemp, Log, TEXT("Delete Player Save Data Succeed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete Player Save Data Failed : no Save Data"));
	}

	if (UGameplayStatics::DoesSaveGameExist(TEXT("LevelData"), 0))
	{
		UGameplayStatics::DeleteGameInSlot(TEXT("LevelData"), 0);
		UE_LOG(LogTemp, Log, TEXT("Delete Level Save Data Succeed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete Level Save Data Failed : no Save Data"));
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
	m_LevelManager = GetSubsystem<ULevelManager>();
}
