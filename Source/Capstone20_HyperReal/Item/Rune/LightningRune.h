// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "LightningRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ULightningRune : public URune
{
	GENERATED_BODY()
	
public:
	ULightningRune();

public:
	virtual void NormalAttackTrigger(AActor* _pActor = nullptr) override;
};
