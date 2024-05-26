// Fill out your copyright notice in the Description page of Project Settings.


#include "Infantry.h"

AInfantry::AInfantry()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -55.f));
	GetMesh()->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mWeaponR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponR"));
	mWeaponR->SetupAttachment(GetMesh(), TEXT("Weapon_Socket_R"));
	// if(mWeaponR->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_Socket_R")))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("WeaponR attached"));
	// }

	mWeaponL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponL"));
	mWeaponL->SetupAttachment(GetMesh(), TEXT("Weapon_Socket_L"));
	//mWeaponL->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_Socket_L"));
	
	mShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	mShield->SetupAttachment(GetMesh(), TEXT("Shield"));
	//mShield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Shield_Socket"));

	mBackpack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backpack"));
	mBackpack->SetupAttachment(GetMesh(), TEXT("Backpack"));
	//mBackpack->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Backpack_Socket"));

	//보병은 기본적으로 airborne이 가능하다.
	bCanAirborne = true;
}

void AInfantry::BeginPlay()
{
	Super::BeginPlay();
	if (mBodyMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mBodyMeshes.Num() - 1);
		GetMesh()->SetSkeletalMesh(mBodyMeshes[RandomIndex]);
	}

	if (mWeaponRMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mWeaponRMeshes.Num() - 1);
		mWeaponR->SetStaticMesh(mWeaponRMeshes[RandomIndex]);
	}

	if (mWeaponLMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mWeaponLMeshes.Num() - 1);
		mWeaponL->SetStaticMesh(mWeaponLMeshes[RandomIndex]);
	}

	if (mBackpackMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mBackpackMeshes.Num() - 1);
		mBackpack->SetStaticMesh(mBackpackMeshes[RandomIndex]);
	}

	
}

void AInfantry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AInfantry::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AInfantry::Attack()
{
	Super::Attack();
}
