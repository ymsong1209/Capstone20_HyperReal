// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerManager.generated.h"

#define STAT_MAX_LEVEL 5

UCLASS()
class CAPSTONE20_HYPERREAL_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDataTable* m_PlayerInfoTable;

	FPlayerInfo m_fPlayerInfo;

	UPROPERTY()
	TArray<int32> m_arrUpgradeCost;

public:
	FPlayerInfo& GetPlayerInfo() { return m_fPlayerInfo; }
	int32 GetUpgradeCost(EPlayerUpgradeType _eType);
	bool IsUpgradeAvail(EPlayerUpgradeType _eType);

	// 룬이 최대 체력을 변경하는 경우가 있기 때문에 필요해짐
	int32 GetHPMax();

public:
	UPlayerManager();
	~UPlayerManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Init(const FString& _fName);

	// 후퇴 시 육체 강화 함수
	void UpgradePlayerStat(EPlayerUpgradeType _eType);

	// 후퇴 시 육체 복구 함수
	void RestoreHealth();

public:
	void SavePlayerInfo(USaveGame* _pSaveGame);
	void LoadPlayerInfo(USaveGame* _pSaveGame);

private:
	void UpgradeAttack(float _fValue);
	void UpgradeHealth(float _fValue);
	void UpgradeSoul(float _fValue);

	// 업그레이드 대성공 일반 등 판정 완벽 x 0.f, 대성공 x 2.5f, 일반 x 1.f
	float CalculateIncreaseRate();
};
