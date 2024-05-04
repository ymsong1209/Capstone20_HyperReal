// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	m_Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	

	SetRootComponent(m_Sphere);

	m_Mesh->SetupAttachment(m_Sphere);
	m_Niagara->SetupAttachment(m_Sphere);
	m_Projectile->SetUpdatedComponent(m_Sphere);

	m_Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	m_Projectile->OnProjectileStop.AddDynamic(this, &AProjectileBase::CollisionStop);
	m_Projectile->OnProjectileBounce.AddDynamic(this, &AProjectileBase::CollisionBounce);
}

void AProjectileBase::CollisionStop(const FHitResult& ImpactResult)
{
	ProjectileStop(ImpactResult);
}

void AProjectileBase::CollisionBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	ProjectileBounce(ImpactResult,ImpactVelocity);
}

void AProjectileBase::ProjectileStop(const FHitResult& ImpactResult)
{
}

void AProjectileBase::ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	m_fAccDistance = m_fMaxDistance;
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//m_fMaxDistance가 -1.f일경우에 무한으로 나감.
	if (m_fMaxDistance > -1.f)
	{
		m_fAccDistance -= m_Projectile->Velocity.Size() * DeltaTime;

		if (0 >= m_fAccDistance)
			Destroy();
	}

	if(m_Target)
	{
		
	}
}

