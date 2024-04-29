// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckDistance.generated.h"

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8 
{
	Trace,
	Attack
};

UCLASS()
class CAPSTONE20_HYPERREAL_API UBTDecorator_CheckDistance : public UBTDecorator
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECheckDistanceType mCheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
public:
	UBTDecorator_CheckDistance();
};
