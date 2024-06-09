// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerManager.h"
#include "../CapStoneGameInstance.h"

UPlayerManager::UPlayerManager()
{
}

UPlayerManager::~UPlayerManager()
{
}

void UPlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPlayerManager::Deinitialize()
{
	Super::Deinitialize();
}

void UPlayerManager::Init(const FString& _fName)
{
	UCapStoneGameInstance* gameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

	if (gameInst)
	{
		const FPlayerDataTableInfo* Info = gameInst->FindPlayerInfo(_fName);

		if (Info)
		{
			UE_LOG(LogTemp, Log, TEXT("PlayerManager Init"));
			m_fPlayerInfo.Name = Info->Name;
			m_fPlayerInfo.Job = Info->Job;
			m_fPlayerInfo.Attack = Info->Attack;
			m_fPlayerInfo.Armor = Info->Armor;
			m_fPlayerInfo.MaxHP = Info->HP;
			m_fPlayerInfo.HP = Info->HP;
			m_fPlayerInfo.MaxSP = Info->SP;
			m_fPlayerInfo.SP = Info->SP;
			m_fPlayerInfo.AttackSpeed = Info->AttackSpeed;
			m_fPlayerInfo.MoveSpeed = Info->MoveSpeed;
			m_fPlayerInfo.CriticalRatio = Info->CriticalRatio;
			m_fPlayerInfo.CriticalDamage = Info->CriticalDamage;
			m_fPlayerInfo.ASkillRatio = Info->ASkillRatio;
			m_fPlayerInfo.SSkillRatio = Info->SSkillRatio;
			m_fPlayerInfo.DSkillRatio = Info->DSkillRatio;
			m_fPlayerInfo.FSkillRatio = Info->FSkillRatio;

			m_fPlayerInfo.ASkillmaxcooltime = Info->ASkillMaxCooltime;
			m_fPlayerInfo.SSkillmaxcooltime = Info->SSkillMaxCooltime;
			m_fPlayerInfo.DSkillmaxcooltime = Info->DSkillMaxCooltime;
			m_fPlayerInfo.FSkillmaxcooltime = Info->FSkillMaxCooltime;

			m_fPlayerInfo.TotalGold = 10000;
			m_fPlayerInfo.LevelAccGold = 0;

			m_fPlayerInfo.AttackLevel = Info->AttackLevel;
			m_fPlayerInfo.HealthLevel = Info->HealthLevel;
			m_fPlayerInfo.SoulLevel = Info->SoulLevel;

			m_fPlayerInfo.AttackProgress = Info->AttackProgress;
			m_fPlayerInfo.HealthProgress = Info->HealthProgress;
			m_fPlayerInfo.SoulProgress = Info->SoulProgress;
		}
	}
}

void UPlayerManager::UpgradePlayerStat(EPlayerUpgradeType _eType)
{
	// 일단 고정수치 100 감소
	m_fPlayerInfo.TotalGold -= 100;

	float fIncreaeMul = CalculateIncreaseRate();

	switch (_eType)
	{
	case EPlayerUpgradeType::Attack:
		UpgradeAttack(fIncreaeMul);
		break;
	case EPlayerUpgradeType::Health:
		UpgradeHealth(fIncreaeMul);
		break;
	case EPlayerUpgradeType::Soul:
		UpgradeSoul(fIncreaeMul);
		break;
	}
}

void UPlayerManager::RestoreHealth()
{
	// 일단 고정수치 100 감소
	m_fPlayerInfo.TotalGold -= 100;

	int32 iRand = FMath::RandRange(20, 80);
	
	m_fPlayerInfo.HP += iRand;

	if (m_fPlayerInfo.MaxHP <= m_fPlayerInfo.HP)
		m_fPlayerInfo.HP = m_fPlayerInfo.MaxHP;
}

void UPlayerManager::UpgradeAttack(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.AttackLevel;
	fUpgradeValue *= _fValue;
	
	if (0.f == _fValue)
	{
		m_fPlayerInfo.AttackProgress = 0.f;
		m_fPlayerInfo.AttackLevel++;

		// 상승 수치 나중에 테이블에 가져오든 해서 변경
		m_fPlayerInfo.Attack += 2;
	}
	else
	{
		m_fPlayerInfo.AttackProgress += fUpgradeValue;

		if (m_fPlayerInfo.AttackProgress >= 100.f)
		{
			m_fPlayerInfo.AttackLevel++;
			m_fPlayerInfo.AttackProgress -= 100.f;

			m_fPlayerInfo.Attack += 2;
		}
	}

	if (m_fPlayerInfo.AttackLevel >= STAT_MAX_LEVEL)
		m_fPlayerInfo.AttackLevel = STAT_MAX_LEVEL;
}

void UPlayerManager::UpgradeHealth(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.HealthLevel;
	fUpgradeValue *= _fValue;

	if (0.f == _fValue)
	{
		m_fPlayerInfo.HealthProgress = 0.f;
		m_fPlayerInfo.HealthLevel++;

		// 상승 수치 나중에 테이블에 가져오든 해서 변경
		m_fPlayerInfo.MaxHP += 200;
	}
	else
	{
		m_fPlayerInfo.HealthProgress += fUpgradeValue;

		if (m_fPlayerInfo.HealthProgress >= 100.f)
		{
			m_fPlayerInfo.HealthLevel++;
			m_fPlayerInfo.HealthProgress -= 100.f;

			m_fPlayerInfo.MaxHP += 200;
		}
	}

	if (m_fPlayerInfo.HealthLevel >= STAT_MAX_LEVEL)
		m_fPlayerInfo.HealthLevel = STAT_MAX_LEVEL;
}

void UPlayerManager::UpgradeSoul(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.SoulLevel;
	fUpgradeValue *= _fValue;

	if (0.f == _fValue)
	{
		m_fPlayerInfo.SoulProgress = 0.f;
		m_fPlayerInfo.SoulLevel++;

		// 상승 수치 나중에 테이블에 가져오든 해서 변경
		m_fPlayerInfo.MaxHP += 200;
	}
	else
	{
		m_fPlayerInfo.SoulProgress += fUpgradeValue;

		if (m_fPlayerInfo.SoulProgress >= 100.f)
		{
			m_fPlayerInfo.SoulLevel++;
			m_fPlayerInfo.SoulProgress -= 100.f;

			m_fPlayerInfo.MaxHP += 200;
		}
	}

	if (m_fPlayerInfo.SoulLevel >= STAT_MAX_LEVEL)
		m_fPlayerInfo.SoulLevel = STAT_MAX_LEVEL;
}

float UPlayerManager::CalculateIncreaseRate()
{
	int32 iRand = FMath::RandRange(1, 100);

	if (iRand <= 10)
		return 0.f;
	else if (iRand <= 20)
		return 2.5f;
	else
		return 1.f;
}