// Fill out your copyright notice in the Description page of Project Settings.


#include "HasteRune.h"

UHasteRune::UHasteRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/swift.swift'")));

	m_fMoveSpeedRatio = 0.1f;
	m_strName = TEXT("신속");
	m_strDesc = TEXT("이동 속도가 상승");
	m_eRuneType = ERuneType::Haste;

	m_pLevelChangeData = &m_fMoveSpeedRatio;
}

void UHasteRune::SetRuneInfo()
{
	SetRuneInfoInner(TEXT("Haste"));
}
