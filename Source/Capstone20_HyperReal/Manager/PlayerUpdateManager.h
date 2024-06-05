// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */
class CAPSTONE20_HYPERREAL_API PlayerUpdateManager
{
private:
	UDataTable* mPlayerInfoTable;

public:
	void SetPlayerDataTable(UDataTable* _pTable) { mPlayerInfoTable = _pTable; }

public:
	PlayerUpdateManager();
	~PlayerUpdateManager();

public:
	void UpgradePlayerStat(const FString& _fName, EPlayerUpgradeType _eType);

private:
	void UpgradeAttack(const FString& _fName);
	void UpgradeHealth(const FString& _fName);
	void UpgradeSoul(const FString& _fName);

	// 업그레이드 대성공 일반 등 판정 0 : 완벽, 1 : 대성공, 2 : 일반
	int32 CalculateSuccess();
};
