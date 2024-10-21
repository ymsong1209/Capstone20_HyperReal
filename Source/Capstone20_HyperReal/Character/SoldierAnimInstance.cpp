// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SkeletonSoldier.h"
#include "Weapon.h"

USoldierAnimInstance::USoldierAnimInstance()	:
	m_iChargeAttackCount(0)
{
	static ConstructorHelpers::FObjectFinder<USoundCue> NormalAttackSoundAsset(TEXT("/Script/Engine.SoundCue'/Game/A_SJWContent/Sound/SC_Skeleton_Normal_Attack.SC_Skeleton_Normal_Attack'"));
	if (NormalAttackSoundAsset.Succeeded())
	{
		m_pSCNormalAttack = NormalAttackSoundAsset.Object;
		UE_LOG(LogTemp, Log, TEXT("Sound Asset Load Succeed"));
	}
	else
		UE_LOG(LogTemp, Log, TEXT("Sound Asset Load Succeed"));
}

void USoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		m_eUsingSkill = pPlayer->GetUsingSkill();
	}
}

void USoldierAnimInstance::AnimNotify_Attack()
{
	Super::AnimNotify_Attack();

	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
		pPlayer->AttackHitCheck();
}

void USoldierAnimInstance::AnimNotify_ChargeAttack()
{
	// 투사체 발사!
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
		pPlayer->EjectChargeSlash();
}

void USoldierAnimInstance::AnimNotify_TrailStart()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		AWeapon* pWeapon = pPlayer->GetRWeapon();

		if (IsValid(pWeapon))
			pWeapon->StartTrail();
	}
}

void USoldierAnimInstance::AnimNotify_TrailEnd()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		AWeapon* pWeapon = pPlayer->GetRWeapon();

		if (IsValid(pWeapon))
			pWeapon->EndTrail();
	}
}

void USoldierAnimInstance::AnimNotify_LeapChargeEnd()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->LeapAttackMove();
	}
}

void USoldierAnimInstance::AnimNotify_LeapAttack()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->AttackLeapAttack();
	}
}

void USoldierAnimInstance::AnimNotify_SkillEnd()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->SkillEnd();
	}
}

void USoldierAnimInstance::AnimNotify_SoundNormalAttack()
{
	ASkeletonSoldier* pPlayer = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_pSCNormalAttack, pPlayer->GetActorLocation());
	}
}
