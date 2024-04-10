// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()	:
	m_fSpeed(0.f)
{
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
		if (pPlayer->OnAttack())
		{
			pPlayer->SetAttack(false);
			UCharacterMovementComponent* pMovement = pPlayer->GetCharacterMovement();
			pMovement->Activate();
		}
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->AttackEnd();
	}
}
