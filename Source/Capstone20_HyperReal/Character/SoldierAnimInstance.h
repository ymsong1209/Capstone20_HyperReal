// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimInstance.h"
#include "SoldierAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API USoldierAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	USoldierAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool m_bOnWhirlwind;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	int32 m_iChargeAttackCount;

public:
	UFUNCTION()
	virtual void AnimNotify_ChargeAttack();

	UFUNCTION()
	virtual void AnimNotify_ChargeAttackEnd();

	UFUNCTION()
	virtual void AnimNotify_TrailStart();

	UFUNCTION()
	virtual void AnimNotify_TrailEnd();
};
