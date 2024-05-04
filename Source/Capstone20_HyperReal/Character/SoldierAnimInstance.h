// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerAnimInstance.h"
#include "SoldierAnimInstance.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API USoldierAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	USoldierAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerSkill m_eUsingSkill;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	int32 m_iChargeAttackCount;

public:
	virtual void AnimNotify_Attack() override;

	UFUNCTION()
	virtual void AnimNotify_ChargeAttack();

	UFUNCTION()
	virtual void AnimNotify_TrailStart();

	UFUNCTION()
	virtual void AnimNotify_TrailEnd();

	UFUNCTION()
	virtual void AnimNotify_LeapChargeEnd();

	UFUNCTION()
	virtual void AnimNotify_LeapAttack();

	UFUNCTION()
	virtual void AnimNotify_SkillEnd();
};
