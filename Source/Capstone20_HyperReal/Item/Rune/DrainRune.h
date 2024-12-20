// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "DrainRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UDrainRune : public URune
{
	GENERATED_BODY()
	
public:
	UDrainRune();

public:
	virtual void SetRuneInfo() override;
	virtual void GiveDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) override;
};
