// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USoldierAnimInstance::USoldierAnimInstance()
{
}

void USoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		UCharacterMovementComponent* pMovement = pPlayer->GetCharacterMovement();
		m_fSpeed = pMovement->Velocity.Size();
	}
}
