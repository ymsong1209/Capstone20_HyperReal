// Fill out your copyright notice in the Description page of Project Settings.


#include "DistortionRune.h"

UDistortionRune::UDistortionRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/distort.distort'")));

	m_fCoolDownRatio = 0.05f;
	m_strName = TEXT("왜곡");
	m_strDesc = TEXT("모든 스킬 쿨타임 감소");
	m_eRuneType = ERuneType::Distortion;
}
