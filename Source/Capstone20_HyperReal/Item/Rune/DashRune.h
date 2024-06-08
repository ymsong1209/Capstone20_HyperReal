// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Rune.h"
#include "DashRune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UDashRune : public URune
{
	GENERATED_BODY()
	
public:
	UDashRune();

public:
	virtual void Activate(AActor* _pActor) override;
};
