// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Enemy_BaseWeapon.h"
#include "EnemyAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetMesh()->bReceivesDecals = false;


	// �ڵ�� �ִϸ��̼� �������Ʈ ����
	// ��ӹ޾Ƽ� ���ġ �ؾ���
	// animationBP ���۷��� ������ _C�� ����ؾ���
	static ConstructorHelpers::FClassFinder<UEnemyAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Animation/ABP_BaseEnemy.ABP_BaseEnemy_C'"));
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	// �ִ� �ν��Ͻ� ����
	AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	// ���� �ִϸ��̼� ���� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimSpawning(TEXT("/Script/Engine.AnimMontage'/Game/A_SYMContent/Animation/AM_BaseEnemy_Spawn.AM_BaseEnemy_Spawn'"));
	if (AnimSpawning.Succeeded())
	{
		SpawnAnimMontage = AnimSpawning.Object;
	}

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	IsSpawned = false;
	CanAttack = false;

	//������ ��Ȱ��ȭ
	GetCharacterMovement()->DisableMovement();

	// Spawn parameters ����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; // �� ���͸� ���ʷ� ����
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Weapon ��ȯ
	Weapon = GetWorld()->SpawnActor<AEnemy_BaseWeapon>(EnemyWeaponClass, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParams);
	if (Weapon) {
		UE_LOG(LogTemp, Display, TEXT("Weapon Spawned"));
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("sheath"));
		Weapon->SetOwner(this);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Spawned"));
	}


	//Spawn animation Montage ����
	// ��Ÿ�� �ʱ�ȭ
	AnimInstance->Montage_SetPosition(SpawnAnimMontage, 0.f);
	AnimInstance->Montage_Play(SpawnAnimMontage);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::AttackMelee()
{
	UE_LOG(LogTemp, Display, TEXT("AttackMelee Called"));

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = GetActorLocation() + GetActorForwardVector() * 250.f;

	FCollisionQueryParams params(NAME_None, false, this);

	TArray<FHitResult> HitArray;
	bool Hit =  GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(50.f), params);

	if (Hit) {
		FColor drawcolor = Hit ? FColor::Red : FColor::Green;

		DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, 150.f, 50.f,
				FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), drawcolor, false, 0.5f);
	}

	CanAttack = true;
}
