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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation",meta = (AllowPrivateAccess = "true"))
	EMonsterAnim mAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool mGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	float fPlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundCue* mHitSound;

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetPlayRate(float NewPlayRate);

	

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

public:
	EMonsterAnim GetAnimType() const{return mAnimType;}
	UFUNCTION(BlueprintCallable)
	void ChangeAnimType(EMonsterAnim _Type);
	FString AnimTypeToString(EMonsterAnim _Type);


};
