// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningRune.h"
#include "TimerManager.h"
#include "../../Projectile/ChainLightning.h"
#include "../../Enemy/Monster.h"

ULightningRune::ULightningRune()	:
	m_bAble(true)
{
	m_TexRune = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_SJWContent/Rune/thunder.thunder'")));

	m_strName = TEXT("번개");
	m_strDesc = TEXT("기본 공격 시 번개가 전이됨");
	m_eRuneType = ERuneType::Lightning;

	// 스태틱 데미지
	m_fEtc = 10.f;
	m_fCoolTime = 1.f;
}

void ULightningRune::NormalAttackTrigger(AActor* _pActor, float _fValue)
{
	if (!m_bAble)
		return;

	m_bAble = false;
	GetWorld()->GetTimerManager().SetTimer(m_hCoolHandle, this, &ULightningRune::CoolDown, m_fCoolTime, false);

	// 체인 라이트닝 투사체 발사
	EjectLightning(_pActor);
}

void ULightningRune::CoolDown()
{
	m_bAble = true;
}

void ULightningRune::EjectLightning(AActor* _pActor)
{
	AMonster* pMon = Cast<AMonster>(_pActor);

	if (!pMon)
		return;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AChainLightning* pLight = GetWorld()->SpawnActor<AChainLightning>(_pActor->GetActorLocation(), _pActor->GetActorRotation(), param);
	pLight->SetDamage(m_fEtc);
	pLight->SetOwnerController(GetWorld()->GetFirstPlayerController());
	pLight->SetTarget(_pActor);
}
