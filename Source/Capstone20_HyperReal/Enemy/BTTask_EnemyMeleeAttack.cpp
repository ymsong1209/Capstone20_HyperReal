#include "BTTask_EnemyMeleeAttack.h"
#include "AIController.h"
#include "BaseEnemy.h"


UBTTask_EnemyMeleeAttack::UBTTask_EnemyMeleeAttack()
{
	NodeName = "EnemyMeleeAttack";
}

EBTNodeResult::Type UBTTask_EnemyMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	/*if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}
	ABaseEnemy* Character = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr) return EBTNodeResult::Failed;
	Character->AttackMelee();*/
	return EBTNodeResult::Succeeded;
}
