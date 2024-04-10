// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "SoldierAnimInstance.h"

ASkeletonSoldier::ASkeletonSoldier()	:
	RWeapon(nullptr)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 86.0f);

	// �޽� �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MesshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ToonSkeletonSoldier/Characters/Meshes/SKM_ToonSkeleton_Soldier_Amethyst.SKM_ToonSkeleton_Soldier_Amethyst'"));
	if (MesshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MesshAsset.Object);

	// �ִϸ��̼� �������Ʈ ����
	static ConstructorHelpers::FClassFinder<USoldierAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SJWContent/Character/AB_SkeletonSoldier.AB_SkeletonSoldier_C'"));
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	// ��Ĺ�� ����
	FName WeaponSocket(TEXT("Weapon_R"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		RWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RWEAPON"));

		// ����Ʈ ���� �ε�
		static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponAsset(TEXT("/Game/ToonSkeletonSoldier/Weapons/Meshes/SM_ShortSword"));
		if (WeaponAsset.Succeeded())
			RWeapon->SetStaticMesh(WeaponAsset.Object);

		RWeapon->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
		RWeapon->SetupAttachment(GetMesh(), WeaponSocket);
	}
}

void ASkeletonSoldier::BeginPlay()
{
	Super::BeginPlay();
}

void ASkeletonSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkeletonSoldier::Attack()
{
	if (m_bOnAttack)
		return;

	// 하고 공격 모션
	if (m_arrAttackMontage.Num() == 0)
	{	
		AttackEnd();
		return;
	}

	if (!m_pAnim->Montage_IsPlaying(m_arrAttackMontage[m_iAttackMontageIndex]))
	{
		// 몽타주 초기화
		m_pAnim->Montage_SetPosition(m_arrAttackMontage[m_iAttackMontageIndex], 0.f);
		m_pAnim->Montage_Play(m_arrAttackMontage[m_iAttackMontageIndex]);

		m_iAttackMontageIndex = (m_iAttackMontageIndex + 1) % m_arrAttackMontage.Num();
	}

	Super::Attack();
}
