// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAttackProjectile.h"

#include "../Character/PlayerCharacter.h"
#include "../Effect/EffectBase.h"

ABossAttackProjectile::ABossAttackProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Weapons/Projectiles/Catapult_rock_lvl3.Catapult_rock_lvl3'"));
	if (MeshAsset.Succeeded())
	{
		m_Mesh->SetStaticMesh(MeshAsset.Object);
		m_Mesh->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("BossAttackMesh setting failed"));
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/ToonTankEffects/P_HitEffect.P_HitEffect'"));
	if (ParticleAsset.Succeeded())
	{
		m_Particle->SetTemplate(ParticleAsset.Object);
	}
	

	m_Projectile->InitialSpeed = 0.f;
	m_Projectile->MaxSpeed = 0.f;
	m_Projectile->ProjectileGravityScale = 1.f;
	m_Projectile->bRotationFollowsVelocity = true;

	m_Capsule->SetCollisionProfileName(TEXT("MonsterObject"));
	m_Capsule->SetCapsuleHalfHeight(70.f);
	m_Capsule->SetCapsuleRadius(70.f);

	//Overlap Event
	m_Capsule->SetGenerateOverlapEvents(false);

	//Hit Event
	m_Capsule->SetNotifyRigidBodyCollision(true);

	m_fMaxDistance = 2000.f;


	static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundAsset(TEXT("/Script/Engine.SoundCue'/Game/A_SJWContent/Sound/SC_Explosion.SC_Explosion'"));
	if (HitSoundAsset.Succeeded())
	{
		mHitSound = HitSoundAsset.Object;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("BossAttack Hit Sound Asset Load Failed"));
	
}

void ABossAttackProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABossAttackProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABossAttackProjectile::ProjectileStop(const FHitResult& ImpactResult)
{
	Super::ProjectileStop(ImpactResult);
	APlayerCharacter* Player = Cast<APlayerCharacter>(ImpactResult.GetActor());
	if(IsValid(Player))
	{
		ImpactResult.GetActor()->TakeDamage(m_Damage,FDamageEvent(),m_OwnerController, this);
		//m_particle 소환
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEffectBase* effect = GetWorld()->SpawnActor<AEffectBase>(ImpactResult.ImpactPoint, GetActorRotation(), param);
		effect->SetParticle(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/ToonTankEffects/P_DeathEffect.P_DeathEffect'"));
		//effect->SetSound(TEXT("/Script/Engine.SoundWave'/Game/Assets/ToonTankEffects/Sounds/Explosion_Cue.Explosion_Cue'"))
	}
	if(IsValid(mHitSound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), mHitSound, GetActorLocation());
	}

	// 보스 터지는 이펙트 호출
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FRotator rot = FRotator::ZeroRotator;
	AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(GetActorLocation(), rot, param);
	Effect->SetNiagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SYMContent/Building/NS_DrirectionSpark_Hit.NS_DrirectionSpark_Hit'"));
	
	Destroy();
}

void ABossAttackProjectile::ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	Super::ProjectileBounce(ImpactResult, ImpactVelocity);
}
