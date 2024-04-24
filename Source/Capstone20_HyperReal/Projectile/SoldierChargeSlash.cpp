// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierChargeSlash.h"

ASoldierChargeSlash::ASoldierChargeSlash()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_SwordSlash.NS_SwordSlash'"));

	if (NiagaraAsset.Succeeded())
		m_Niagara->SetAsset(NiagaraAsset.Object);
	

	m_Projectile->InitialSpeed = 1000.f;
	m_Projectile->MaxSpeed = 1000.f;
	m_Projectile->ProjectileGravityScale = 0.f;

	m_fMaxDistance = 500.f;
}

void ASoldierChargeSlash::BeginPlay()
{
	Super::BeginPlay();
	m_Projectile->Velocity = GetActorForwardVector() * m_Projectile->InitialSpeed;
}

void ASoldierChargeSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
