// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAttackProjectile.h"

#include "../Character/PlayerCharacter.h"

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
		UE_LOG(LogTemp, Warning, TEXT("projectile hit called"));
	}
	Destroy();
}

void ABossAttackProjectile::ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	Super::ProjectileBounce(ImpactResult, ImpactVelocity);
}
