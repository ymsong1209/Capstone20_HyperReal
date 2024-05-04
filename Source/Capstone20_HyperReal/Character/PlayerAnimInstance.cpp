// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()	:
	m_fSpeed(0.f)
{
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		UCharacterMovementComponent* pMovement = pPlayer->GetCharacterMovement();
		m_fSpeed = pMovement->Velocity.Size();

		m_bOnAttack = pPlayer->OnAttack();
	}
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	// 공격 충돌체 생성
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->AttackCombo();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		if (pPlayer->IsComboDectected())
			pPlayer->AttackReset();
		else
			pPlayer->AttackEnd();
	}
}
