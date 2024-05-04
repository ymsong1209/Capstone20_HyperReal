// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectTarget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBTService_DetectTarget : public UBTService
{
	GENERATED_BODY()
private:
	FTimerHandle TimerHandle;
	UBehaviorTreeComponent* CachedOwnerComp;
public:
	void ClearTimerAndSetInterval();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
public:
	UBTService_DetectTarget();
	
};
