// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"
#include "MonsterAIController.h"

UMonsterAnimInstance::UMonsterAnimInstance()
	:mAnimType(EMonsterAnim::Idle),
	mGround(true),
	fPlayRate(1.f)
{
}



void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster)) {
		UCharacterMovementComponent* Movement = Monster->GetCharacterMovement();

		mGround = Movement->IsMovingOnGround();
	}
}

void UMonsterAnimInstance::SetPlayRate(float NewPlayRate)
{
	fPlayRate = NewPlayRate;
	if (UAnimSequence* AnimSequence = Cast<UAnimSequence>(GetCurrentActiveMontage()))
	{
		AnimSequence->RateScale = fPlayRate;
	}
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(Monster)) {
		Monster->DeathEnd();
	}
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_AttackEnd"));
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(Monster)) {
		Monster->SetAttackEnd(true);
	}
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_AttackCalled"));
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(Monster)) {
		Monster->Attack();
	}
}

void UMonsterAnimInstance::AnimNotify_HitStart()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(Monster)) {
		Monster->SetCanAttack(false);
		if (AAIController* AIController = Cast<AAIController>(Monster->GetController()))
		{
			AIController->UnPossess(); // 몬스터 컨트롤 연결
		}
	}
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(Monster)) {
		Monster->SetCanAttack(true);
		//기존에 만들어뒀던 ai다시 장착
		AAIController* AIController = Monster->GetAIController();
		AIController->Possess(Monster); // 몬스터 컨트롤 연결
	}
}
