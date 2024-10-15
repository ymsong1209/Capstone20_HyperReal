// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "CapStoneGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UCapStoneGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UDataTable* mPlayerInfoTable;

	UPROPERTY()
	UDataTable* mMonsterInfoTable;

	UPROPERTY()
	UDataTable* mBuildingInfoTable;

	UPROPERTY()
	class UPlayerManager* m_PlayerManager;

	UPROPERTY()
	class URuneManager* m_RuneManager;

	UPROPERTY()
	class ULevelManager* m_LevelManager;
	

public:
	const FMonsterDataTableInfo* FindMonsterInfo(const FString& _Name);
	const FPlayerDataTableInfo* FindPlayerInfo(const FString& _Name);
	const FBuildingDataTableInfo* FindBuildingInfo(const FString& _Name);

	void UpdatePlayerGold(const FString& PlayerName, int _gold);

	UPlayerManager* GetPlayerManager() { return m_PlayerManager; }
	URuneManager* GetRuneManager() { return m_RuneManager; }
	ULevelManager* GetLevelManager() const { return m_LevelManager; }

public:
	void SaveGameData();
	void LoadGameData();
	
	void SavePlayerData();
	void LoadPlayerData();
	
	void SaveLevelData();
	void LoadLevelData();

public:
	virtual void Init() override;

public:
	UCapStoneGameInstance();

public:
	void UpgradePlayerStat(EPlayerUpgradeType _eType);
	void UpgradeRune(ERuneType _eType);
	void UpgradeHealth();
};
