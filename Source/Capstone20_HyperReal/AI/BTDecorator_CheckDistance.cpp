// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"
#include "../Enemy/MonsterAIController.h"
#include "../Enemy/Monster.h"


UBTDecorator_CheckDistance::UBTDecorator_CheckDistance()
{
	mCheckType = ECheckDistanceType::Trace;
	NodeName = TEXT("CheckDistance");
}

bool UBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Monster) return false;

	AActor* Target = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target) return false;

	//몬스터와 target의 위치를 얻어옴
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	//두 위치의 높이를 맞춰줌
	MonsterLoc.Z = TargetLoc.Z;

	//두 위치 사이의 거리를 구함
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	float CheckDistance = 0.f;


	switch (mCheckType)
	{
	case ECheckDistanceType::Trace:
		return true;
		{
			//유한 추적 할라면 활성화
			CheckDistance = Monster->GetMonsterInfo().TraceDistance;
		}
		break;
	case ECheckDistanceType::Attack:
		CheckDistance = Monster->GetMonsterInfo().AttackDistance;
		break;
	default:
		break;
	}


	return Distance<=CheckDistance;
}
