// Fill out your copyright notice in the Description page of Project Settings.


#include "ThornRune.h"

UThornRune::UThornRune()
{
	m_fEtc = 10.f;
	m_strName = TEXT("가시");
	m_strDesc = TEXT("피격 시 근접한 적에게 피해");
	m_eRuneType = ERuneType::Thorn;
}

void UThornRune::TakeDamageTrigger(AActor* _pActor, float _fValue)
{
	// 주변에 데미지 주기
}
