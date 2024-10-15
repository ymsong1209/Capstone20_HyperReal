// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "ResurrectionRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UResurrectionRune : public URune
{
	GENERATED_BODY()
	
public:
	UResurrectionRune();

public:
	virtual void SetRuneInfo() override;
	virtual void Activate(AActor* _pActor = nullptr, float _fValue = 0.f) override;
};
