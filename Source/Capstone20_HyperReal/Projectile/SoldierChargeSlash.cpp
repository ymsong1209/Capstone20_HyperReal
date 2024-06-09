// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierChargeSlash.h"

#include "../Enemy/Monster.h"

ASoldierChargeSlash::ASoldierChargeSlash()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Capsule->SetCollisionProfileName(TEXT("PlayerObject"));
	m_Capsule->InitCapsuleSize(100.f, 50.f);
	m_Capsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	m_Capsule->OnComponentBeginOverlap.AddDynamic(this, &ASoldierChargeSlash::SlashBeginOverlap);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_SwordSlash.NS_SwordSlash'"));

	if (NiagaraAsset.Succeeded())
		m_Niagara->SetAsset(NiagaraAsset.Object);

	m_Niagara->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));
	m_Niagara->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	m_Projectile->InitialSpeed = 1000.f;
	m_Projectile->MaxSpeed = 1000.f;
	m_Projectile->ProjectileGravityScale = 0.f;

	m_fMaxDistance = 700.f;
	m_Damage = 0.f;
}

void ASoldierChargeSlash::BeginPlay()
{
	Super::BeginPlay();
}

void ASoldierChargeSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLoc = GetActorLocation() + m_Projectile->MaxSpeed * GetActorForwardVector() * DeltaTime;
	SetActorLocation(NewLoc);
}

void ASoldierChargeSlash::SlashBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->TakeDamage(m_Damage, FDamageEvent(), m_OwnerController, this) != -1)
		{
			AMonster* pMon = Cast<AMonster>(OtherActor);

			if (pMon)
			{

			}
		}
	}
}