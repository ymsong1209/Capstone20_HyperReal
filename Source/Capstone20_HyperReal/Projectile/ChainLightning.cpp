// Fill out your copyright notice in the Description page of Project Settings.


#include "ChainLightning.h"
#include "../Enemy/Monster.h"
#include "../Effect/EffectBase.h"

AChainLightning::AChainLightning()	:
	m_pCurrentLight(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	m_Capsule->SetCollisionProfileName(TEXT("PlayerObject"));
	m_Capsule->InitCapsuleSize(10.f, 10.f);
	//m_Capsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	//m_Capsule->OnComponentBeginOverlap.AddDynamic(this, &AChainLightning::BeginOverlap);

	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/Mage/LightningShield/NS_Mage_LIghtningShield.NS_Mage_LIghtningShield'"));

	//if (NiagaraAsset.Succeeded())
	//	m_Niagara->SetAsset(NiagaraAsset.Object);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LightningAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_Chain_Lightning.NS_Chain_Lightning'"));

	if (LightningAsset.Succeeded())
		m_Lightning = LightningAsset.Object;

	//m_Niagara->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));
	//m_Niagara->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	//m_Projectile->InitialSpeed = 10000.f;
	//m_Projectile->MaxSpeed = 1000.f;
	m_Projectile->ProjectileGravityScale = 0.f;
	m_fRange = 1000.f;
	m_fMaxDistance = -1.f;

	m_iChainCount = 4;
}

void AChainLightning::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_Target))
		SpawnLightning();
}

void AChainLightning::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	if (!IsValid(m_Target))
	{
		Destroy();

		if (IsValid(m_pCurrentLight))
			m_pCurrentLight->SetLifeSpan(2.f);

		return;
	}

	if (IsValid(m_pCurrentLight))
		m_pCurrentLight->GetNiagaraCom()->SetVectorParameter(FName("User.Beam_End"), GetActorLocation());

	FVector vDir = (m_Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	SetActorRotation(vDir.Rotation());

	FVector NewLoc = (GetActorLocation() + (vDir * 1500.f * DeltaTime));
	SetActorLocation(NewLoc);

	// 타겟에 데미지 주고 새로운 타겟 설정
	float fDist = FVector::Distance(m_Target->GetActorLocation(), GetActorLocation());
	if (fDist <= 10.f)
	{
		if (m_Target->TakeDamage(m_Damage, FDamageEvent(), m_OwnerController, this) != -1)
		{
			//AMonster* pMon = Cast<AMonster>(m_Target);

			//if (pMon)
			//{
			//}

			FindNewTarget();
			SpawnLightning();
		}

		//AMonster* pMon = Cast<AMonster>(m_Target);
		//if (pMon)
		//	FindNewTarget();
	}
}

void AChainLightning::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->TakeDamage(m_Damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this) == -1)
		{
			AMonster* pMon = Cast<AMonster>(OtherActor);

			if (pMon)
			{
			}
			FindNewTarget();
		}
	}
}

void AChainLightning::FindNewTarget()
{
	m_arrTarget.Add(m_Target);

	if (--m_iChainCount <= 0)
	{
		m_Target = nullptr;
		return;
	}

	TArray<AActor*> FoundMon;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundMon);

	float fMin = 1000000.f;
	AActor* pNext = nullptr;

	for (int32 i = 0; i < FoundMon.Num(); i++)
	{
		AMonster* pMon = Cast<AMonster>(FoundMon[i]);

		if (m_arrTarget.Find(pMon) == INDEX_NONE)
		{
			float fDist = FVector::Distance(pMon->GetActorLocation(), GetActorLocation());
			if (fDist <= fMin && fDist <= m_fRange)
			{
				pNext = pMon;
			}
		}
	}

	m_Target = pNext;
}

void AChainLightning::SpawnLightning()
{
	if (!m_Lightning)
		return;

	if (IsValid(m_pCurrentLight))
	{
		m_pCurrentLight->SetLifeSpan(2.f);
		m_pCurrentLight = nullptr;	
	}

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	m_pCurrentLight = GetWorld()->SpawnActor<AEffectBase>(GetActorLocation(), GetActorRotation(), param);
	m_pCurrentLight->SetNiagara(m_Lightning);

	m_pCurrentLight->GetNiagaraCom()->SetVectorParameter(FName("User.Beam_Start"), m_Target->GetActorLocation());
}
