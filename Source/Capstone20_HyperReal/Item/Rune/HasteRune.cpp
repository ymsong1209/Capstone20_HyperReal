// Fill out your copyright notice in the Description page of Project Settings.


#include "HasteRune.h"

UHasteRune::UHasteRune()
{
	m_fMoveSpeedRatio = 0.1f;
	m_strName = TEXT("신속");
	m_strDesc = TEXT("이동 속도가 상승");
	m_eRuneType = ERuneType::Haste;
}