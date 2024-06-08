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

public:
	FPlayerInfo& GetPlayerInfo() { return m_fPlayerInfo; }

public:
	UPlayerManager();
	~UPlayerManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Init(const FString& _fName);
	void UpgradePlayerStat(EPlayerUpgradeType _eType);

private:
	void UpgradeAttack(float _fValue);
	void UpgradeHealth(float _fValue);
	void UpgradeSoul(float _fValue);

	// 업그레이드 대성공 일반 등 판정 완벽 x 0.f, 대성공 x 2.5f, 일반 x 1.f
	float CalculateIncreaseRate();
};
