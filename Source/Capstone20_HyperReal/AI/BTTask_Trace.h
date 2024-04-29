// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Trace.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBTTask_Trace : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
public:
	UBTTask_Trace();
};
