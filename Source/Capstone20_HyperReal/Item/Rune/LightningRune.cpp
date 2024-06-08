// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningRune.h"

ULightningRune::ULightningRune()
{
	m_fEtc = 10.f;
	m_strName = TEXT("번개");
	m_strDesc = TEXT("기본 공격 시 번개가 전이됨");
	m_eRuneType = ERuneType::Lightning;
}

void ULightningRune::NormalAttackTrigger(AActor* _pActor)
{
	// 체인 라이트닝 투사체 발사

	// 타이머 만들어서 쿨타임 구현
}