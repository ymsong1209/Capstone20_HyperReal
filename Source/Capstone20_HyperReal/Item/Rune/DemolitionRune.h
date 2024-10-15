// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "DemolitionRune.generated.h"

/**
 * 파괴의 룬
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UDemolitionRune : public URune
{
	GENERATED_BODY()
	
public:
	UDemolitionRune();

public:
	virtual void SetRuneInfo() override;
};
