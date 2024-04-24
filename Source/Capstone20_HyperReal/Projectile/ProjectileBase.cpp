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

	if (m_fMaxDistance >= 0)
	{
		m_fAccDistance -= m_Projectile->Velocity.Size() * DeltaTime;

		if (0 >= m_fAccDistance)
			Destroy();
	}
}

