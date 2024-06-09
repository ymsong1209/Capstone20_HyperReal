// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
private:
	bool mbIsPossesed;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* mAITree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBlackboardData* mAIBlackboard;
	
public:
	bool IsPossesed() const { return mbIsPossesed; }
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
public:
	AMonsterAIController();
};
