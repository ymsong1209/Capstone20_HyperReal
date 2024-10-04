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
	m_iCost(100)
{
}

void URune::Updgrade()
{
	// 나중에 최대 레벨인지 체크하는 코드 추가해야함
	m_iLevel++;
	m_iCost += 100;
	UE_LOG(LogTemp, Log, TEXT("Rune Type : %d, Rune Level %d"), (int32)m_eRuneType, (int32)m_iLevel);
}
