// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "DistortionRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UDistortionRune : public URune
{
	GENERATED_BODY()

public:
	UDistortionRune();

public:
	virtual void SetRuneInfo() override;
};
