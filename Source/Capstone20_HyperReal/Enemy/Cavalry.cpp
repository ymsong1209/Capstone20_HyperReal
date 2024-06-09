// Fill out your copyright notice in the Description page of Project Settings.


#include "Cavalry.h"
#include "MonsterAnimInstance.h"

ACavalry::ACavalry()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(95.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
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

	mQuiver = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backpack"));
	mQuiver->SetupAttachment(GetMesh(), TEXT("Backpack_Socket"));
	mQuiver->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mQuiver->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	
	mShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	mShield->SetupAttachment(GetMesh(), TEXT("Shield_Socket"));
	mShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mShield->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mHead = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	mHead->SetupAttachment(GetMesh());
	mHead->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mHead->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mHead->bReceivesDecals = false;
	
	mBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	mBody->SetupAttachment(GetMesh());
	mBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBody->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mBody->bReceivesDecals = false;

	
	
	//기마병은 기본적으로 airborne이 불가능하다.
	bCanAirborne = false;
}

void ACavalry::BeginPlay()
{
	Super::BeginPlay();

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

	if (mQuiverMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mQuiverMeshes.Num() - 1);
		mQuiver->SetStaticMesh(mQuiverMeshes[RandomIndex]);
	}

	if (mShieldMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mShieldMeshes.Num() - 1);
		mShield->SetStaticMesh(mShieldMeshes[RandomIndex]);
	}
	
	if (mHorseMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mHorseMeshes.Num() - 1);
		GetMesh()->SetSkeletalMesh(mHorseMeshes[RandomIndex]);
	}
	if (mHeadMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mHeadMeshes.Num() - 1);
		mHead->SetSkeletalMesh(mHeadMeshes[RandomIndex]);
	}
	if (mBodyMeshes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, mBodyMeshes.Num() - 1);
		mBody->SetSkeletalMesh(mBodyMeshes[RandomIndex]);
	}

	UMonsterAnimInstance* horseAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	UMonsterAnimInstance* bodyAnim = Cast<UMonsterAnimInstance>(mBody->GetAnimInstance());
	UMonsterAnimInstance* headAnim = Cast<UMonsterAnimInstance>(mHead->GetAnimInstance());

	if(!horseAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("Horse Anim Instance is nullptr"));
	}
	if(!bodyAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Anim Instance is nullptr"));
	}
	if(!headAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("Head Anim Instance is nullptr"));
	}
	AnimInstances.Add(horseAnim);
	AnimInstances.Add(bodyAnim);
	AnimInstances.Add(headAnim);
	
}

void ACavalry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACavalry::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ACavalry::Attack()
{
	Super::Attack();
}
