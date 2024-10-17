// Fill out your copyright notice in the Description page of Project Settings.


#include "DashRune.h"
#include "../../Character/PlayerCharacter.h"

UDashRune::UDashRune()	:
	m_bDashAble(true)
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/leap.leap'")));

	m_strName = TEXT("도약");
	m_strDesc = TEXT("대쉬 기술을 습득");
	m_eRuneType = ERuneType::Dash;

	//m_iLevel = 1;
	m_fEtc = 1.f;

	m_pLevelChangeData = &m_fEtc;
}

void UDashRune::SetRuneInfo()
{
	SetRuneInfoInner(TEXT("Dash"));
}

void UDashRune::Activate(AActor* _pActor, float _fValue)
{
	if (m_iLevel == 0 || m_bDashAble == false)
		return;

	// 플레이어 도약 실행
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(_pActor);

	if (IsValid(pPlayer))
	{
		pPlayer->Dash();
		m_bDashAble = false;
		// 타이머를 이용해서 쿨타임 계산
		GetWorld()->GetTimerManager().SetTimer(m_hDashCoolHandle, this, &UDashRune::DashCoolEnd, m_fEtc, false);
	}
}

void UDashRune::DashCoolEnd()
{
	m_bDashAble = true;
}
