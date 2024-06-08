// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationRune.h"

URotationRune::URotationRune()
{
	m_fEtc = 2.f;
	m_strName = TEXT("회전");
	m_strDesc = TEXT("회전베기 지속시간 증가");
	m_eRuneType = ERuneType::Rotation;
}
