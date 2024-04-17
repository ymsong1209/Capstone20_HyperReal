// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void AnimNotify_Attack();

};
