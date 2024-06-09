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
	
private:
	bool m_bAble;
	FTimerHandle m_hCoolHandle;

public:
	ULightningRune();

public:
	virtual void NormalAttackTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) override;

private:
	void CoolDown();
	void EjectLightning(AActor* _pActor);
};
