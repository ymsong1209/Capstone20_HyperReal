// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoutArrow.h"
#include "Particles/ParticleSystem.h"
//#include "../Effect/EffectBase.h"

AScoutArrow::AScoutArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Weapons/Projectiles/Arrow_A.Arrow_A'"));
	if (MeshAsset.Succeeded())
	{
		m_Mesh->SetStaticMesh(MeshAsset.Object);
		m_Mesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		m_Mesh->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ArrowMesh setting failed"));
	}

	// static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/Archer/ArrowFire/NS_Archer_Arrow_Fire.NS_Archer_Arrow_Fire'"));
	//
	// if (NiagaraAsset.Succeeded())
	// 	m_Niagara->SetAsset(NiagaraAsset.Object);

	

	m_Projectile->InitialSpeed = 1000.f;
	m_Projectile->MaxSpeed = 1000.f;
	m_Projectile->ProjectileGravityScale = 0.f;
	m_Projectile->bRotationFollowsVelocity = true;

	m_Capsule->SetCollisionProfileName(TEXT("MonsterObject"));

	//Overlap Event
	m_Capsule->SetGenerateOverlapEvents(true);

	//Hit Event
	m_Capsule->SetNotifyRigidBodyCollision(true);

	m_fMaxDistance = 2000.f;

}

void AScoutArrow::BeginPlay()
{
	Super::BeginPlay();
	m_PrevLoc = GetActorLocation();
}

void AScoutArrow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AScoutArrow::ProjectileStop(const FHitResult& ImpactResult)
{
	Super::ProjectileStop(ImpactResult);

	// //화살 맞는 이펙트 발생
	// FActorSpawnParameters param;
	// param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//
	// AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(GetActorLocation(), GetActorRotation(), param);
	//
	// Effect->SetParticle(TEXT(""));
	// Effect->SetSound(TEXT(""));
	//
	// FVector DecalLoc = GetActorLocation();
	// DecalLoc.Z -=88.f;
	
	
	ImpactResult.GetActor()->TakeDamage(m_Damage,FDamageEvent(),m_OwnerController, this);
	UE_LOG(LogTemp, Warning, TEXT("CollisionStopCalled"));
	Destroy();
}

void AScoutArrow::ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	Super::ProjectileBounce(ImpactResult, ImpactVelocity);
	UE_LOG(LogTemp, Warning, TEXT("CollisionBounceCalled"));
}
