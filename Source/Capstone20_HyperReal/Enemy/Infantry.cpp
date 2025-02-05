// Fill out your copyright notice in the Description page of Project Settings.


#include "Infantry.h"
#include "MonsterAnimInstance.h"
#include "Capstone20_HyperReal/InGameModeBase.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "InfantryShell.h"

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

	UMonsterAnimInstance* bodyAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	UMonsterAnimInstance* headAnim = Cast<UMonsterAnimInstance>(mHead->GetAnimInstance());
	
	AnimInstances.Add(bodyAnim);
	AnimInstances.Add(headAnim);
	
	if (!IsValid(mInfantryShell))
	{
		UE_LOG(LogTemp, Error, TEXT("No InfantryShell"));
		return;
	}
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	// Body Mesh 랜덤 적용
	if (mInfantryShell->mBodyMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mInfantryShell->mBodyMeshes.Num() - 1);
		GetMesh()->SetSkeletalMesh(mInfantryShell->mBodyMeshes[RandomIndex]);
	}

	// Weapon R
	if (mInfantryShell->mWeaponRMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mInfantryShell->mWeaponRMeshes.Num() - 1);
		mWeaponR->SetStaticMesh(mInfantryShell->mWeaponRMeshes[RandomIndex]);
	}

	// Weapon L
	if (mInfantryShell->mWeaponLMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mInfantryShell->mWeaponLMeshes.Num() - 1);
		mWeaponL->SetStaticMesh(mInfantryShell->mWeaponLMeshes[RandomIndex]);
	}

	// Backpack
	if (mInfantryShell->mBackpackMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mInfantryShell->mBackpackMeshes.Num() - 1);
		mBackpack->SetStaticMesh(mInfantryShell->mBackpackMeshes[RandomIndex]);
	}

	// Head
	if (mInfantryShell->mHeadMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mInfantryShell->mHeadMeshes.Num() - 1);
		mHead->SetSkeletalMesh(mInfantryShell->mHeadMeshes[RandomIndex]);
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
