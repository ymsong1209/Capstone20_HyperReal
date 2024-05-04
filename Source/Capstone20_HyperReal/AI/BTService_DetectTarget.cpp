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

void UBTService_DetectTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	CachedOwnerComp = nullptr;  // �ʱ�ȭ
}

void UBTService_DetectTarget::ClearTimerAndSetInterval()
{
	if(!CachedOwnerComp) return;
	AAIController* Controller = Cast<AMonsterAIController>(CachedOwnerComp->GetAIOwner());
	if (!Controller) return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if (!Monster) return;
	Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	Monster->SetActorTickInterval(0.5f);
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	CachedOwnerComp = &OwnerComp;
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
	
	//플레이어가 주변에 있을시
	if (Hit) {
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
		Monster->SetActorTickInterval(0.f);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	//플레이어가 주변에 없으면 Player추적 종료
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTService_DetectTarget::ClearTimerAndSetInterval, 2.0f, false);
	}
}
