// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneManager.h"
#include "../Item/Rune/Rune.h"
#include "../Item/Rune/RotationRune.h"
#include "../Item/Rune/LightningRune.h"
#include "../Item/Rune/ExtremeRune.h"
#include "../Item/Rune/DemolitionRune.h"
#include "../Item/Rune/DashRune.h"
#include "../Item/Rune/DrainRune.h"
#include "../Item/Rune/HasteRune.h"
#include "../Item/Rune/ThornRune.h"
#include "../Item/Rune/DistortionRune.h"
#include "../Item/Rune/ResurrectionRune.h"

#include "../CapStoneGameInstance.h"
#include "PlayerManager.h"
#include "../Save/PlayerUpgradeSaveGame.h"

URuneManager::URuneManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> RuneDataTableAsset(TEXT("/Script/Engine.DataTable'/Game/A_SJWContent/Rune/RuneDT.RuneDT'"));
	if (RuneDataTableAsset.Succeeded()) {
		m_pRuneDataTable = RuneDataTableAsset.Object;
		UE_LOG(LogTemp, Log, TEXT("Load Rune Data Table Succeed"));
	}
}

URuneManager::~URuneManager()
{
}

void URuneManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Init();
}

void URuneManager::Deinitialize()
{
	Super::Deinitialize();
}

void URuneManager::Init()
{
	// 룬 초기화
	m_arrRune[(int)ERuneType::Rotation] = NewObject<URotationRune>(this, URotationRune::StaticClass());
	m_arrRune[(int)ERuneType::Lightning] = NewObject<ULightningRune>(this, ULightningRune::StaticClass());
	m_arrRune[(int)ERuneType::Extreme] = NewObject<UExtremeRune>(this, UExtremeRune::StaticClass());
	m_arrRune[(int)ERuneType::Demolition] = NewObject<UDemolitionRune>(this, UDemolitionRune::StaticClass());
	m_arrRune[(int)ERuneType::Dash] = NewObject<UDashRune>(this, UDashRune::StaticClass());
	m_arrRune[(int)ERuneType::Drain] = NewObject<UDrainRune>(this, UDrainRune::StaticClass());
	m_arrRune[(int)ERuneType::Haste] = NewObject<UHasteRune>(this, UHasteRune::StaticClass());
	m_arrRune[(int)ERuneType::Thorn] = NewObject<UThornRune>(this, UThornRune::StaticClass());
	m_arrRune[(int)ERuneType::Distortion] = NewObject<UDistortionRune>(this, UDistortionRune::StaticClass());
	m_arrRune[(int)ERuneType::Resurrection] = NewObject<UResurrectionRune>(this, UResurrectionRune::StaticClass());

	for (int i = 0; i < (int)ERuneType::End; i++)
	{
		if (m_arrRune[i])
			m_arrRune[i]->SetDataTable(m_pRuneDataTable);
	}

	// 룬 코스트 데이터 가져오기
	if (m_pRuneDataTable)
	{
		FRuneDataTableInfo* pInfo = m_pRuneDataTable->FindRow<FRuneDataTableInfo>(FName("Cost"), TEXT(""));

		if (pInfo)
		{
			m_fRuneCostInfo.Level1Value = pInfo->Level1Value;
			m_fRuneCostInfo.Level2Value = pInfo->Level2Value;
			m_fRuneCostInfo.Level3Value = pInfo->Level3Value;
			m_fRuneCostInfo.Level4Value = pInfo->Level4Value;
			m_fRuneCostInfo.Level5Value = pInfo->Level5Value;
		}
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("No Rune Data Table"));
}

void URuneManager::GiveDamageTrigger(AActor* _pActor, float _fValue)
{
	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			m_arrRune[i]->GiveDamageTrigger(_pActor, _fValue);
		}
	}
}

void URuneManager::NormalAttackTrigger(AActor* _pActor, float _fValue)
{
	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			m_arrRune[i]->NormalAttackTrigger(_pActor, _fValue);
		}
	}
}

void URuneManager::TakeDamageTrigger(AActor* _pActor, float _fValue)
{
	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			m_arrRune[i]->TakeDamageTrigger(_pActor, _fValue);
		}
	}
}

void URuneManager::Activate(AActor* _pActor, float _fValue)
{
	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			m_arrRune[i]->TakeDamageTrigger(_pActor, _fValue);
		}
	}
}

float URuneManager::GetHealthAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetHealthRatio();
		}
	}

	return fResult;
}

float URuneManager::GetSoulAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetSoulRatio();
		}
	}

	return fResult;
}

float URuneManager::GetAttackAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetAttackRatio();
		}
	}

	return fResult;
}

float URuneManager::GetAttackSpeedAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetAttackSpeedRatio();
		}
	}

	return fResult;
}

float URuneManager::GetMoveSpeedAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetMoveSpeedRatio();
		}
	}

	return fResult;
}

float URuneManager::GetCoolDownAdd()
{
	float fResult = 1.f;

	for (int32 i = 0; i < (int32)ERuneType::End; i++)
	{
		if (m_arrRune[i] && m_arrRune[i]->GetLevel() > 0)
		{
			fResult *= m_arrRune[i]->GetCoolDownRatio();
		}
	}
	return fResult;
}

void URuneManager::UpgradeRune(ERuneType _eType)
{
	URune* pRune = m_arrRune[(int32)_eType];
	UCapStoneGameInstance* gameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

	if (gameInst)
	{
		gameInst->GetPlayerManager()->GetPlayerInfo().TotalGold -= GetRuneCost(_eType);
		UE_LOG(LogTemp, Log, TEXT("Upgrade Rune, Cost : %d"), GetRuneCost(_eType));
	}

	pRune->Updgrade();
}

int32 URuneManager::GetRuneCost(ERuneType _eType)
{
	int32 iLevel = m_arrRune[(int)_eType]->GetLevel();
	int32 iCost = 0;

	switch (iLevel)
	{
	case 0:
		iCost = (int32)m_fRuneCostInfo.Level1Value;
		break;
	case 1:
		iCost = (int32)m_fRuneCostInfo.Level2Value;
		break;
	case 2:
		iCost = (int32)m_fRuneCostInfo.Level3Value;
		break;
	case 3:
		iCost = (int32)m_fRuneCostInfo.Level4Value;
		break;
	case 4:
		iCost = (int32)m_fRuneCostInfo.Level5Value;
		break;
	}

	return iCost;
}

void URuneManager::SaveRuneLevels(USaveGame* _pSaveGame)
{
	UPlayerUpgradeSaveGame* pSaveInst = Cast<UPlayerUpgradeSaveGame>(_pSaveGame);

	if (pSaveInst)
	{
		for (int32 i = 0; i < (int32)ERuneType::End; i++)
		{
			if (nullptr == m_arrRune[i])
			{
				UE_LOG(LogTemp, Error, TEXT("Save Rune Levels Error, Rune is Null"));
				continue;
			}

			pSaveInst->m_arrRuneLevels.Add(m_arrRune[i]->GetLevel());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Rune Levels Failed, Save Instance is Null"));
	}
}

void URuneManager::LoadRuneLevels(USaveGame* _pSaveGame)
{
	UPlayerUpgradeSaveGame* pLoadInst = Cast<UPlayerUpgradeSaveGame>(_pSaveGame);

	if (pLoadInst)
	{
		for (int32 i = 0; i < pLoadInst->m_arrRuneLevels.Num(); i++)
		{
			if (nullptr == m_arrRune[i])
			{
				UE_LOG(LogTemp, Error, TEXT("Load Rune Levels Error, Rune is Null"));
				continue;
			}

			m_arrRune[i]->SetLevel(pLoadInst->m_arrRuneLevels[i]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Rune Levels Failed, Load Instance is Null"));
	}
}
