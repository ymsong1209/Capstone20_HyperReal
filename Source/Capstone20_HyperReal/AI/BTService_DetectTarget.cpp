// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"
#include "../Enemy/Monster.h"
#include "../Enemy/MonsterAIController.h"


UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	//tick�� 0.5�� +=0.1�� ���̿� �ѹ� �۵���
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

	//�ֺ��� �÷��̾ �ִ��� �Ǵ�.
	FHitResult result;
	bool Hit = GetWorld()->SweepSingleByChannel(result, Monster->GetActorLocation(),
		Monster->GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(Info.TraceDistance), params);
	
	//�÷��̾ �ֺ��� ������
	if (Hit) {
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
		Monster->SetActorTickInterval(0.f);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	//�÷��̾ �ֺ��� ������ Player���� ����
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTService_DetectTarget::ClearTimerAndSetInterval, 2.0f, false);
	}
}
