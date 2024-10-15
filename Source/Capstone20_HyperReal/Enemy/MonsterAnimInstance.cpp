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
		//UE_LOG(LogTemp,Display,TEXT("AttackEnd"));
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
	Monster->GetAIController()->GetBlackboardComponent()->SetValueAsObject(("Target"), nullptr);
	//UE_LOG(LogTemp, Warning, TEXT("HitStart"))
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	Monster->GetAIController()->GetBlackboardComponent()->SetValueAsObject(("Target"), Character);
	//UE_LOG(LogTemp, Warning, TEXT("HitEnd"));		
}

void UMonsterAnimInstance::ChangeAnimType(EMonsterAnim _Type)
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (!Monster)
	{
		UE_LOG(LogTemp, Error, TEXT("ChangeAnimType failed: Monster is nullptr"));
		return;
	}
    
	//FString AnimTypeString = AnimTypeToString(_Type);
	// UE_LOG(LogTemp, Warning, TEXT("ChangeAnimType at Monster: %s to AnimType: %s"), *Monster->GetName(), *AnimTypeString);
	if(_Type == EMonsterAnim::Idle)
	{
		int a = 0;
	}
	mAnimType = _Type;
}

FString UMonsterAnimInstance::AnimTypeToString(EMonsterAnim _Type)
{
	switch (_Type)
	{
	case EMonsterAnim::Idle: return "Idle";
	case EMonsterAnim::Walk: return "Walk";
	case EMonsterAnim::Run: return "Run";
	case EMonsterAnim::Attack: return "Attack";
	case EMonsterAnim::Death: return "Death";
	case EMonsterAnim::Hit: return "Hit";
	case EMonsterAnim::Stun: return "Stun";
	case EMonsterAnim::Airborne: return "Airborne";
	case EMonsterAnim::Skill1: return "Skill1";
	case EMonsterAnim::Skill2: return "Skill2";
	case EMonsterAnim::Skill3: return "Skill3";
	case EMonsterAnim::Skill4: return "Skill4";
	default: return "Unknown";
	}
}
