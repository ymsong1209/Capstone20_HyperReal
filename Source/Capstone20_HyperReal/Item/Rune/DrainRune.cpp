// Fill out your copyright notice in the Description page of Project Settings.


#include "DrainRune.h"
#include "../../Character/PlayerCharacter.h"

UDrainRune::UDrainRune()
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/bloodsteal.bloodsteal'")));

	m_fEtc = 0.05f;
	m_strName = TEXT("흡혈");
	m_strDesc = TEXT("준 피해에 비례하여 체력 회복");
	m_eRuneType = ERuneType::Drain;
}

void UDrainRune::GiveDamageTrigger(AActor* _pActor, float _fValue)
{
	// 흡혈 호출
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (IsValid(pPlayer))
	{
		float fHeal = _fValue * m_fEtc;
		pPlayer->Heal(fHeal);
	}
}