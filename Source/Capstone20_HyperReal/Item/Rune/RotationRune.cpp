// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationRune.h"

URotationRune::URotationRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/rotate.rotate'")));
	m_strName = TEXT("회전");
	m_strDesc = TEXT("회전베기 지속시간 증가");
	m_eRuneType = ERuneType::Rotation;

	// 지속시간 증가률
	m_fEtc = 2.f;
	m_pLevelChangeData = &m_fEtc;
}

void URotationRune::SetRuneInfo()
{
	SetRuneInfoInner(TEXT("Rotation"));
}
