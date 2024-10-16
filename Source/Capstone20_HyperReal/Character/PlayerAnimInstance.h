// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float m_fSpeed;

public:
	UFUNCTION()
	virtual void AnimNotify_Attack();

	UFUNCTION()
	virtual void AnimNotify_AttackCombo();

	UFUNCTION()
	virtual void AnimNotify_AttackEnd();
};
