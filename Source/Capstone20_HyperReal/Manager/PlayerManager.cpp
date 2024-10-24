// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerManager.h"
#include "../CapStoneGameInstance.h"
#include "../Save/PlayerUpgradeSaveGame.h"
#include "../BaseLevelGameModeBase.h"
#include "../UI/BaseLevelWidget.h"
#include "../UI/BasecampWidget.h"
#include "../UI/UpgradeWidget.h"

UPlayerManager::UPlayerManager()	:
	m_PlayerInfoTable(nullptr)
{
	m_arrUpgradeCost.Reserve(STAT_MAX_LEVEL);
	m_arrUpgradeCost.Add(100);
	m_arrUpgradeCost.Add(150);
	m_arrUpgradeCost.Add(200);
	m_arrUpgradeCost.Add(250);
	m_arrUpgradeCost.Add(300);
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
			UE_LOG(LogTemp, Warning, TEXT("PlayerManager Init"));
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

			m_fPlayerInfo.TotalGold = Info->TotalGold;
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
	m_fPlayerInfo.TotalGold -= GetUpgradeCost(_eType);
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

int32 UPlayerManager::GetUpgradeCost(EPlayerUpgradeType _eType)
{
	int iLevel = 0;
	switch (_eType)
	{
	case EPlayerUpgradeType::Attack:
		iLevel = GetPlayerInfo().AttackLevel;
		break;
	case EPlayerUpgradeType::Health:
		iLevel = GetPlayerInfo().HealthLevel;
		break;
	case EPlayerUpgradeType::Soul:
		iLevel = GetPlayerInfo().SoulLevel;
		break;
	}

	return m_arrUpgradeCost[iLevel - 1];
}

bool UPlayerManager::IsUpgradeAvail(EPlayerUpgradeType _eType)
{
	if (GetUpgradeCost(_eType) >= GetPlayerInfo().TotalGold)
		return true;
	else
		return false;
}

void UPlayerManager::RestoreHealth()
{
	// 일단 고정수치 100 감소
	m_fPlayerInfo.TotalGold -= 100;

	int32 iRand = FMath::RandRange(10, 25);
	
	m_fPlayerInfo.HP += (int)((float)iRand / 100 * m_fPlayerInfo.MaxHP);

	if (m_fPlayerInfo.MaxHP <= m_fPlayerInfo.HP)
		m_fPlayerInfo.HP = m_fPlayerInfo.MaxHP;
}

void UPlayerManager::SavePlayerInfo(USaveGame* _pSaveGame)
{
	UPlayerUpgradeSaveGame* pSaveInst = Cast<UPlayerUpgradeSaveGame>(_pSaveGame);

	if (pSaveInst)
	{
		pSaveInst->m_fPlayerInfo = m_fPlayerInfo;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Player Info Failed, Save Instance is Null"));
	}
}

void UPlayerManager::LoadPlayerInfo(USaveGame* _pSaveGame)
{
	UPlayerUpgradeSaveGame* pLoadInst = Cast<UPlayerUpgradeSaveGame>(_pSaveGame);

	if (pLoadInst)
	{
		m_fPlayerInfo = pLoadInst->m_fPlayerInfo;
		UE_LOG(LogTemp, Log, TEXT("Player Info Load Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Player Info Failed, Load Instance is Null"));
	}
}

void UPlayerManager::UpgradeAttack(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.AttackLevel;
	fUpgradeValue *= _fValue;
	ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
	GameMode->GetUBaseLevelWidget()->GetBasecampWidget()->GetUpgradeWidget()->StartComboTextEffect((int)fUpgradeValue);
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

			m_fPlayerInfo.Attack += 6;
		}
	}

	if (m_fPlayerInfo.AttackLevel >= STAT_MAX_LEVEL)
	{
		m_fPlayerInfo.AttackLevel = STAT_MAX_LEVEL;
		m_fPlayerInfo.AttackProgress = 100.f;
	}

	UE_LOG(LogTemp, Log, TEXT("Attack Level : %d, Attack : %d, progress : %f"), m_fPlayerInfo.AttackLevel, m_fPlayerInfo.Attack,m_fPlayerInfo.AttackProgress);
}

void UPlayerManager::UpgradeHealth(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.HealthLevel;
	fUpgradeValue *= _fValue;
	ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
	GameMode->GetUBaseLevelWidget()->GetBasecampWidget()->GetUpgradeWidget()->StartComboTextEffect((int)fUpgradeValue);
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
	{
		m_fPlayerInfo.HealthProgress = 100.f;
		m_fPlayerInfo.HealthLevel = STAT_MAX_LEVEL;
	}

	UE_LOG(LogTemp, Log, TEXT("Health Level : %d, Health : %d"), m_fPlayerInfo.HealthLevel, m_fPlayerInfo.MaxHP);
}

void UPlayerManager::UpgradeSoul(float _fValue)
{
	float fUpgradeValue = 20.f - (float)m_fPlayerInfo.SoulLevel;
	fUpgradeValue *= _fValue;
	ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
	GameMode->GetUBaseLevelWidget()->GetBasecampWidget()->GetUpgradeWidget()->StartComboTextEffect((int)fUpgradeValue);
	if (0.f == _fValue)
	{
		m_fPlayerInfo.SoulProgress = 0.f;
		m_fPlayerInfo.SoulLevel++;

		// 상승 수치 나중에 테이블에 가져오든 해서 변경
		m_fPlayerInfo.MaxSP += 20;
	}
	else
	{
		m_fPlayerInfo.SoulProgress += fUpgradeValue;

		if (m_fPlayerInfo.SoulProgress >= 100.f)
		{
			m_fPlayerInfo.SoulLevel++;
			m_fPlayerInfo.SoulProgress -= 100.f;

			m_fPlayerInfo.MaxSP += 200;
		}
	}

	if (m_fPlayerInfo.SoulLevel >= STAT_MAX_LEVEL)
	{
		m_fPlayerInfo.SoulLevel = STAT_MAX_LEVEL;
		m_fPlayerInfo.SoulProgress = 100.f;
	}

	UE_LOG(LogTemp, Log, TEXT("Soul Level : %d, Soul : %d"), m_fPlayerInfo.SoulLevel, m_fPlayerInfo.MaxSP);
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
