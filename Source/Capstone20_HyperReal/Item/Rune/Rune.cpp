// Fill out your copyright notice in the Description page of Project Settings.


#include "Rune.h"
#include "../../Manager/PlayerManager.h"

URune::URune()	:
	m_eRuneType(ERuneType::End),
	m_iLevel(0),
	m_fHealthRatio(0.f),
	m_fSoulRatio(0.f),
	m_fAttackRatio(0.f),
	m_fAttackSpeedRatio(0.f),
	m_fMoveSpeedRatio(0.f),
	m_fCoolDownRatio(0.f),
	m_fEtc(0.f),
	m_fAccCoolTime(0.f),
	m_fCoolTime(0.f),
	m_pLevelChangeData(nullptr),
	m_pRuneDataTable(nullptr)
{
}

void URune::SetLevel(int32 _iLevel)
{
	m_iLevel = _iLevel;

	if (m_pLevelChangeData)
	{
		switch (_iLevel)
		{
		case 1:
			(*m_pLevelChangeData) = m_fRuneInfo.Level1Value;
			break;
		case 2:
			(*m_pLevelChangeData) = m_fRuneInfo.Level2Value;
			break;
		case 3:
			(*m_pLevelChangeData) = m_fRuneInfo.Level3Value;
			break;
		case 4:
			(*m_pLevelChangeData) = m_fRuneInfo.Level4Value;
			break;
		case 5:
			(*m_pLevelChangeData) = m_fRuneInfo.Level5Value;
			break;
		}

		UE_LOG(LogTemp, Log, TEXT("Rune Data Upgrade Complete : %f"), *m_pLevelChangeData);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Level Change Data not Set"));
}

void URune::Updgrade()
{	
	SetLevel(++m_iLevel);
	UE_LOG(LogTemp, Log, TEXT("Rune Type : %d, Rune Level %d, Rune Value %f"), (int32)m_eRuneType, (int32)m_iLevel, *m_pLevelChangeData);
}

void URune::SetRuneInfoInner(FStringView _strName)
{
	if (!m_pRuneDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("No Rune Data Table"));
		return;
	}

	FRuneDataTableInfo* pInfo = m_pRuneDataTable->FindRow<FRuneDataTableInfo>(FName(_strName), TEXT(""));
	if (pInfo)
	{
		m_fRuneInfo.Name = pInfo->Name;
		m_fRuneInfo.Level1Value = pInfo->Level1Value;
		m_fRuneInfo.Level2Value = pInfo->Level2Value;
		m_fRuneInfo.Level3Value = pInfo->Level3Value;
		m_fRuneInfo.Level4Value = pInfo->Level4Value;
		m_fRuneInfo.Level5Value = pInfo->Level5Value;

		UE_LOG(LogTemp, Log, TEXT("Rune Data Load Succeed"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("row not exist"));
}