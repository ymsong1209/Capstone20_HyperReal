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

void UResurrectionRune::SetLevel(int32 _iLevel)
{
	m_iLevel = _iLevel;

	if (m_pLevelChangeData)
	{
		switch (_iLevel)
		{
		case 1:
			(*m_pLevelChangeData) += m_fRuneInfo.Level1Value;
			break;
		case 2:
			(*m_pLevelChangeData) += m_fRuneInfo.Level2Value;
			break;
		case 3:
			(*m_pLevelChangeData) += m_fRuneInfo.Level3Value;
			break;
		case 4:
			(*m_pLevelChangeData) += m_fRuneInfo.Level4Value;
			break;
		case 5:
			(*m_pLevelChangeData) += m_fRuneInfo.Level5Value;
			break;
		}

		UE_LOG(LogTemp, Log, TEXT("Rune Data Upgrade Complete : %f"), *m_pLevelChangeData);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Level Change Data not Set"));
}
