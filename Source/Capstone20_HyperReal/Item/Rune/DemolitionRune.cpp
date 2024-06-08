// Fill out your copyright notice in the Description page of Project Settings.


#include "DemolitionRune.h"

UDemolitionRune::UDemolitionRune()
{
	m_fEtc = 0.1f;
	m_strName = TEXT("파괴");
	m_strDesc = TEXT("건물에 주는 피해 증가");
	m_eRuneType = ERuneType::Demolition;
}
