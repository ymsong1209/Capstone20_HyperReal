#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyMeleeAttack.generated.h"

/**
 *
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBTTask_EnemyMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UBTTask_EnemyMeleeAttack();
};
