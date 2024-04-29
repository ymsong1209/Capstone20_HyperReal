// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"
#include "../Enemy/Monster.h"
#include "../Enemy/MonsterAIController.h"


UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	//tick이 0.5초 +=0.1초 사이에 한번 작동됨
	Interval = 0.5f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller) return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster) return;

	const FMonsterInfo& Info = Monster->GetMonsterInfo();

	FCollisionQueryParams params(NAME_None, false, Monster);

	//주변에 플레이어가 있는지 판단.
	FHitResult result;
	bool Hit = GetWorld()->SweepSingleByChannel(result, Monster->GetActorLocation(),
		Monster->GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(Info.TraceDistance), params);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), Info.TraceDistance, 20,
		DrawColor, false, 0.3f);
#endif

	if (Hit) {
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}
	else {
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}