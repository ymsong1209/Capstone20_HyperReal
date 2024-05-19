// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EMonsterAnim : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Hit,
	Stun,
	Airborne,
	Skill1,
	Skill2,
	Skill3,
	Skill4
};

UCLASS()
class CAPSTONE20_HYPERREAL_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAnim mAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool mGround;

public:
	EMonsterAnim GetAnimType() const
	{
		return mAnimType;
	}

	UFUNCTION(BlueprintCallable)
	void ChangeAnimType(EMonsterAnim _Type){ 
		mAnimType = _Type;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_HitStart();
	
	UFUNCTION()
	void AnimNotify_HitEnd();

};
