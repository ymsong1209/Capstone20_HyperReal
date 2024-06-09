// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "ThornRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UThornRune : public URune
{
	GENERATED_BODY()
	
public:
	UThornRune();

public:
	virtual void TakeDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) override;
};
