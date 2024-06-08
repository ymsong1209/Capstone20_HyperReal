// Fill out your copyright notice in the Description page of Project Settings.


#include "ResurrectionRune.h"

UResurrectionRune::UResurrectionRune()
{
	m_fEtc = 1.f;
	m_strName = TEXT("부활");
	m_strDesc = TEXT("1회에 한해 부활 가능");
	m_eRuneType = ERuneType::Resurrection;
}

void UResurrectionRune::Activate(AActor* _pActor)
{
	// 캐릭터 부활
}
