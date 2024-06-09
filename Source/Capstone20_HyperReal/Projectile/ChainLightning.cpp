// Fill out your copyright notice in the Description page of Project Settings.


#include "ChainLightning.h"
#include "../Enemy/Monster.h"

AChainLightning::AChainLightning()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	m_Capsule->SetCollisionProfileName(TEXT("PlayerObject"));
	m_Capsule->InitCapsuleSize(10.f, 10.f);
	//m_Capsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	//m_Capsule->OnComponentBeginOverlap.AddDynamic(this, &AChainLightning::BeginOverlap);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_Energy_1.NS_Energy_1'"));

	if (NiagaraAsset.Succeeded())
		m_Niagara->SetAsset(NiagaraAsset.Object);

	//m_Niagara->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));
	//m_Niagara->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	m_Projectile->InitialSpeed = 10000.f;
	m_Projectile->MaxSpeed = 1000.f;
	m_Projectile->ProjectileGravityScale = 0.f;
	m_fRange = 300.f;
	m_fMaxDistance = -1.f;

	m_iChainCount = 4;
}

void AChainLightning::SetTarget(AActor* Target)
{
	m_Target = Target;
	m_arrTarget.Add(m_Target);
}

void AChainLightning::BeginPlay()
{
	Super::BeginPlay();
}

void AChainLightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(m_Target))
	{
		Destroy();
		return;
	}

	//FVector vDir = (m_Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	//SetActorRotation(vDir.Rotation());

	//FVector NewLoc = GetActorLocation() + (GetActorForwardVector() * m_Projectile->MaxSpeed * DeltaTime);
	//SetActorLocation(NewLoc);


	// 타겟에 데미지 주고 새로운 타겟 설정
	float fDist = FVector::Distance(m_Target->GetActorLocation(), GetActorLocation());
	if (fDist <= 5.f)
	{
		if (m_Target->TakeDamage(m_Damage, FDamageEvent(), m_OwnerController, this) != -1)
		{
			AMonster* pMon = Cast<AMonster>(m_Target);

			FindNewTarget();

			if (pMon)
			{

			}
		}
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
				UE_LOG(LogTemp, Log, TEXT("Attack Mon count : %d"), m_iChainCount);
				FindNewTarget();
			}
		}
	}
}

void AChainLightning::FindNewTarget()
{
	if (--m_iChainCount <= 0)
	{
		m_Target = nullptr;
		return;
	}

	TArray<AActor*> FoundMon;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundMon);

	//UE_LOG(LogTemp, Log, TEXT("Monster Count : %d Chain Count : %d"), FoundMon.Num(), m_iChainCount);
	
	float fMin = MAX_FLT;
	AActor* pNext = nullptr;

	for (AActor* actor : FoundMon)
	{
		AMonster* pMon = Cast<AMonster>(actor);

		if (IsValid(pMon) && (m_arrTarget.Find(pMon) == INDEX_NONE))
		{
			float fDist = FVector::Distance(pMon->GetActorLocation(), GetActorLocation());
			if (fDist <= fMin && fDist >= m_fRange)
				pNext = pMon;
		}
	}

	if (pNext)
	{
		m_arrTarget.Add(pNext);
		UE_LOG(LogTemp, Log, TEXT("ligtning find new target"));
	}
	m_Target = pNext;
}
