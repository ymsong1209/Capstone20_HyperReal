// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()	:
	m_ASWeapon(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::StartTrail()
{
	if(m_ASWeapon)
		WeaponMesh->PlayAnimation(m_ASWeapon, true);
}

void AWeapon::EndTrail()
{
	if (m_ASWeapon)
		WeaponMesh->SetAnimation(nullptr);
}


