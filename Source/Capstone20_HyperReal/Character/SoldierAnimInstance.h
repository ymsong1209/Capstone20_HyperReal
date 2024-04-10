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

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
