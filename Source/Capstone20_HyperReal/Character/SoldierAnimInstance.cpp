// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstance.h"
#include "SkeletonSoldier.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SkeletonSoldier.h"
#include "Weapon.h"

USoldierAnimInstance::USoldierAnimInstance()	:
	m_iChargeAttackCount(0),
	m_bOnWhirlwind(false)
{
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
		m_bOnWhirlwind = (pPlayer->GetUsingSkill() == EPlayerSkill::SkillA);
	}
}

void USoldierAnimInstance::AnimNotify_ChargeAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Charge Attack"));
}

void USoldierAnimInstance::AnimNotify_ChargeAttackEnd()
{
	ASkeletonSoldier* pSoldier = Cast<ASkeletonSoldier>(TryGetPawnOwner());

	if (++m_iChargeAttackCount >= pSoldier->GetChargeAttackCount())
	{
		Montage_Stop(0.1f);
		m_iChargeAttackCount = 0;
	}
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
