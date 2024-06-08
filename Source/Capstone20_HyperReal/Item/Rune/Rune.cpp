// Fill out your copyright notice in the Description page of Project Settings.


#include "Rune.h"

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
	m_fCoolTime(0.f)
{
}

void URune::GiveDamageTrigger(AActor* _pActor)
{
}

void URune::NormalAttackTrigger(AActor* _pActor)
{
}

void URune::TakeDamageTrigger(AActor* _pActor)
{
}

void URune::Activate(AActor* _pActor)
{
}
