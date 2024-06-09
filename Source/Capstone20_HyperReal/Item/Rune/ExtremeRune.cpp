// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtremeRune.h"

UExtremeRune::UExtremeRune()
{
	m_fAttackRatio = 0.35f;
	m_fHealthRatio = -0.25f;
	m_strName = TEXT("극단");
	m_strDesc = TEXT("최대 체력 감소, 공격력 증가");
	m_eRuneType = ERuneType::Extreme;
}