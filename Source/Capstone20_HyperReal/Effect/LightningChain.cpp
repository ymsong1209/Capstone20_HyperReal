// Fill out your copyright notice in the Description page of Project Settings.


#include "../Effect/LightningChain.h"
#include "../Enemy/Monster.h"
#include "../Effect/EffectBase.h"

// Sets default values
ALightningChain::ALightningChain()	:
	m_iChainCount(0),
	m_fRange(1000.f),
	m_Target(nullptr),
	m_fDamage(0.f),
	m_pCurLightEffect(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LightningAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_Chain_Lightning.NS_Chain_Lightning'"));

	if (LightningAsset.Succeeded())
	{
		m_Lightning = LightningAsset.Object;
		UE_LOG(LogTemp, Log, TEXT("Lightning Load Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lightning Load failed"));
	}

	m_iChainCount = 4;
}

// Called when the game starts or when spawned
void ALightningChain::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_Target))
	{
		UE_LOG(LogTemp, Log, TEXT("Target exist, check and spawn chain lightning"));
		GetWorld()->GetTimerManager().SetTimer(m_hSpawnTimerHandle, this, &ALightningChain::CheckAndSpawn, 0.1f, true);
	}
}

// Called every frame
void ALightningChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(m_Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target was null, destory chain lightning"));
		Destroy();

		if (GetWorldTimerManager().IsTimerActive(m_hSpawnTimerHandle))
			GetWorld()->GetTimerManager().ClearTimer(m_hSpawnTimerHandle);

		if (IsValid(m_pCurLightEffect))
			m_pCurLightEffect->SetLifeSpan(0.1f);

		return;
	}
}

void ALightningChain::CheckAndSpawn()
{
	FindNewTarget();

	if (IsValid(m_Target))
	{
		UE_LOG(LogTemp, Log, TEXT("Found New Target Spawn Effect"));
		SpawnLightning();
	}
}

void ALightningChain::FindNewTarget()
{
	m_arrTarget.Add(m_Target);
	m_Target->TakeDamage(m_fDamage, FDamageEvent(), nullptr, this);
	SpawnHitEffect(m_Target->GetActorLocation(), m_Target->GetActorRotation());
	m_vPrevLoc = m_Target->GetActorLocation();

	UE_LOG(LogTemp, Log, TEXT("Hit Target Chain Count : %d"), m_iChainCount);

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
			float fDist = FVector::Distance(pMon->GetActorLocation(), m_vPrevLoc);
			if (fDist <= fMin && fDist <= m_fRange)
			{
				UE_LOG(LogTemp, Log, TEXT("Found New Target"));
				pNext = pMon;
			}
		}
	}

	m_Target = pNext;
}

void ALightningChain::SpawnLightning()
{
	if (IsValid(m_pCurLightEffect))
	{
		m_pCurLightEffect->SetLifeSpan(0.1f);
		m_pCurLightEffect = nullptr;
	}

	if (!m_Lightning || !IsValid(m_Target))
		return;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	m_pCurLightEffect = GetWorld()->SpawnActor<AEffectBase>(GetActorLocation(), GetActorRotation(), param);
	m_pCurLightEffect->SetNiagara(m_Lightning);
	m_pCurLightEffect->GetNiagaraCom()->SetVectorParameter(FName("User.Beam_Start"), m_vPrevLoc);
	m_pCurLightEffect->GetNiagaraCom()->SetVectorParameter(FName("User.Beam_End"), m_Target->GetActorLocation());

	UE_LOG(LogTemp, Log, TEXT("Beam start : %s"), *m_vPrevLoc.ToString());
	UE_LOG(LogTemp, Log, TEXT("Beam start : %s"), *m_Target->GetActorLocation().ToString());
}

void ALightningChain::SpawnHitEffect(FVector _vLoc, FRotator _vRot)
{
	FActorSpawnParameters param;

	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(_vLoc, _vRot, param);

	Effect->SetNiagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_Lightning_Slash_Impact.NS_Lightning_Slash_Impact'"));
}

