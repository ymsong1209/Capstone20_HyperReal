// Fill out your copyright notice in the Description page of Project Settings.


#include "ResurrectionRune.h"
#include "../../Character/PlayerCharacter.h"

UResurrectionRune::UResurrectionRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/revive.revive'")));

	m_fEtc = 1.f;
	m_strName = TEXT("부활");
	m_strDesc = TEXT("1회에 한해 부활 가능");
	m_eRuneType = ERuneType::Resurrection;

	m_pLevelChangeData = &m_fEtc;
}

void UResurrectionRune::SetRuneInfo()
{
	SetRuneInfoInner(TEXT("Resurrection"));
}

void UResurrectionRune::Activate(AActor* _pActor, float _fValue)
{
	if (m_iLevel <= 0)
		return;

	// 캐릭터 부활
	int32 iCount = (int32)m_fEtc;

	if (iCount > 0)
	{
		m_fEtc -= 1.f;
		APlayerCharacter* pPlayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (IsValid(pPlayer))
		{
			pPlayer->Ressurection(0.5f);
		}
	}
}
