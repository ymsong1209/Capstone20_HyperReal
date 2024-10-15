// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "ExtremeRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UExtremeRune : public URune
{
	GENERATED_BODY()
	
public:
	UExtremeRune();

public:
	virtual void SetRuneInfo() override;
};
