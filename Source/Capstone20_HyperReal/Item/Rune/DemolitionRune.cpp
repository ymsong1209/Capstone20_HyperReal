// Fill out your copyright notice in the Description page of Project Settings.


#include "DemolitionRune.h"

UDemolitionRune::UDemolitionRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/destroy.destroy'")));

	m_strName = TEXT("파괴");
	m_strDesc = TEXT("건물에 주는 피해 증가");
	m_eRuneType = ERuneType::Demolition;

	m_fEtc = 1.1f;
	m_pLevelChangeData = &m_fEtc;
}

void UDemolitionRune::SetRuneInfo()
{
	SetRuneInfoInner(TEXT("Demolition"));
}
