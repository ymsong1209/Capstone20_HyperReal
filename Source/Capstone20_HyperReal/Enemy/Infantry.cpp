// Fill out your copyright notice in the Description page of Project Settings.


#include "Infantry.h"
#include "MonsterAnimInstance.h"

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
	mWeaponR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mWeaponR->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	
	mWeaponL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponL"));
	mWeaponL->SetupAttachment(GetMesh(), TEXT("Weapon_Socket_L"));
	mWeaponL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mWeaponL->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	
	mShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	mShield->SetupAttachment(GetMesh(), TEXT("Shield"));
	mShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mShield->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mBackpack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backpack"));
	mBackpack->SetupAttachment(GetMesh(), TEXT("Backpack"));
	mBackpack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBackpack->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mHead = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	mHead->SetupAttachment(GetMesh());
	mHead->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mHead->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mHead->bReceivesDecals = false;

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
	
	if (mHeadMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mHeadMeshes.Num() - 1);
		mHead->SetSkeletalMesh(mHeadMeshes[RandomIndex]);
	}

	UMonsterAnimInstance* bodyAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	UMonsterAnimInstance* headAnim = Cast<UMonsterAnimInstance>(mHead->GetAnimInstance());
	
	AnimInstances.Add(bodyAnim);
	AnimInstances.Add(headAnim);
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
