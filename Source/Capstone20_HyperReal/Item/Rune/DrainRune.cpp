// Fill out your copyright notice in the Description page of Project Settings.


#include "DrainRune.h"

UDrainRune::UDrainRune()
{
	m_fEtc = 0.05f;
	m_strName = TEXT("흡혈");
	m_strDesc = TEXT("준 피해에 비례하여 체력 회복");
	m_eRuneType = ERuneType::Drain;
}

void UDrainRune::GiveDamageTrigger(AActor* _pActor, float _fValue)
{
	// 흡혈 호출
}