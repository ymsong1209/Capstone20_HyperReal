// Fill out your copyright notice in the Description page of Project Settings.


#include "DistortionRune.h"

UDistortionRune::UDistortionRune()
{
	m_fCoolDownRatio = 0.05f;
	m_strName = TEXT("왜곡");
	m_strDesc = TEXT("모든 스킬 쿨타임 감소");
	m_eRuneType = ERuneType::Distortion;
}
