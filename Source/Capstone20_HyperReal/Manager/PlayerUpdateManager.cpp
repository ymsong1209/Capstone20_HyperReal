// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUpdateManager.h"

PlayerUpdateManager::PlayerUpdateManager()
{
}

PlayerUpdateManager::~PlayerUpdateManager()
{
}

void PlayerUpdateManager::UpgradePlayerStat(const FString& _fName, EPlayerUpgradeType _eType)
{
	switch (_eType)
	{
	case EPlayerUpgradeType::Attack:
		UpgradeAttack(_fName);
		break;
	case EPlayerUpgradeType::Health:
		UpgradeHealth(_fName);
		break;
	case EPlayerUpgradeType::Soul:
		UpgradeSoul(_fName);
		break;
	}
}

void PlayerUpdateManager::UpgradeAttack(const FString& _fName)
{
	FPlayerDataTableInfo* fInfo = mPlayerInfoTable->FindRow<FPlayerDataTableInfo>(*_fName, TEXT(""));

	float fUpgradeValue = 20.f - (float)fInfo->AttackLevel;
	int32 iSuccess = CalculateSuccess();

	switch (iSuccess)
	{
		// 완벽
	case 0:
		fUpgradeValue = 100.f;
		break;
		// 대성공
	case 1:
		fUpgradeValue *= 2.5f;
		break;
	}

	fInfo->AttackProgress += fUpgradeValue;

	if (fInfo->AttackProgress >= 100.f)
	{
		fInfo->AttackLevel++;
		fInfo->AttackProgress -= 100.f;
	}
}

void PlayerUpdateManager::UpgradeHealth(const FString& _fName)
{
	FPlayerDataTableInfo* fInfo = mPlayerInfoTable->FindRow<FPlayerDataTableInfo>(*_fName, TEXT(""));

	float fUpgradeValue = 20.f - (float)fInfo->HealthLevel;
	int32 iSuccess = CalculateSuccess();

	switch (iSuccess)
	{
		// 완벽
	case 0:
		fUpgradeValue = 100.f;
		break;
		// 대성공
	case 1:
		fUpgradeValue *= 2.5f;
		break;
	}

	fInfo->HealthProgress += fUpgradeValue;

	if (fInfo->HealthProgress >= 100.f)
	{
		fInfo->HealthLevel++;
		fInfo->HealthProgress -= 100.f;
	}
}

void PlayerUpdateManager::UpgradeSoul(const FString& _fName)
{
	FPlayerDataTableInfo* fInfo = mPlayerInfoTable->FindRow<FPlayerDataTableInfo>(*_fName, TEXT(""));

	float fUpgradeValue = 20.f - (float)fInfo->SoulLevel;
	int32 iSuccess = CalculateSuccess();

	switch (iSuccess)
	{
		// 완벽
	case 0:
		fUpgradeValue = 100.f;
		break;
		// 대성공
	case 1:
		fUpgradeValue *= 2.5f;
		break;
	}

	fInfo->SoulProgress += fUpgradeValue;

	if (fInfo->SoulProgress >= 100.f)
	{
		fInfo->SoulLevel++;
		fInfo->SoulProgress -= 100.f;
	}
}

int32 PlayerUpdateManager::CalculateSuccess()
{
	int32 iRand = FMath::RandRange(1, 100);

	if (iRand <= 10)
		return 0;
	else if (iRand <= 20)
		return 1;
	else
		return 2;
}
