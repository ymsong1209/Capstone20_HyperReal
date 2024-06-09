// Fill out your copyright notice in the Description page of Project Settings.


#include "ThornRune.h"

UThornRune::UThornRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/thorn.thorn'")));

	m_fEtc = 10.f;
	m_strName = TEXT("가시");
	m_strDesc = TEXT("피격 시 근접한 적에게 피해");
	m_eRuneType = ERuneType::Thorn;
}

void UThornRune::TakeDamageTrigger(AActor* _pActor, float _fValue)
{
	// 활쟁이는 나중에 고민해봄
	_pActor->TakeDamage(m_fEtc, FDamageEvent(), GetWorld()->GetFirstPlayerController(), GetWorld()->GetFirstPlayerController()->GetPawn());
}
