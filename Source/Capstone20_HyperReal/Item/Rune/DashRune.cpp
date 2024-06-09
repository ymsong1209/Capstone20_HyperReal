// Fill out your copyright notice in the Description page of Project Settings.


#include "DashRune.h"

UDashRune::UDashRune()
{
	m_strName = TEXT("도약");
	m_strDesc = TEXT("대쉬 기술을 습득");
	m_eRuneType = ERuneType::Dash;
}

void UDashRune::Activate(AActor* _pActor, float _fValue)
{
	// 플레이어 도약 실행
}
