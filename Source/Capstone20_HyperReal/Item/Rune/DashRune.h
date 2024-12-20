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

private:
	FTimerHandle m_hDashCoolHandle;
	bool m_bDashAble;
	
public:
	UDashRune();

public:
	virtual void SetRuneInfo() override;
	virtual void Activate(AActor* _pActor = nullptr, float _fValue = 0.f) override;

private:
	void DashCoolEnd();
};
