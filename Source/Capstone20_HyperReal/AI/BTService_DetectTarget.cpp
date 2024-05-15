// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"
#include "../Enemy/Monster.h"
#include "../Enemy/MonsterAIController.h"


UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	//tick이 0.5초 +=0.1초 사이에 한번 작동됨
	Interval = 0.5f;
	//timer초기화
	TimerHandle.Invalidate();
}

void UBTService_DetectTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	CachedOwnerComp = nullptr;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	CachedOwnerComp = &OwnerComp;

	TracePlayer(OwnerComp);
}


void UBTService_DetectTarget::TracePlayer(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		UE_LOG(LogTemp, Display, TEXT("no controller"));
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if (!Monster) {
		UE_LOG(LogTemp, Display, TEXT("no monster"));
		return;
	}

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player){
		UE_LOG(LogTemp, Display, TEXT("no player"));
		return;
	}
	
	AActor* TargetActor = Cast<AActor>(Player);
	bool canattack = Monster->GetCanAttack();
	if(canattack)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), TargetActor);
	}
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
	Monster->SetActorTickInterval(0.f);
}

void UBTService_DetectTarget::CheckPlayerInTraceDistance(UBehaviorTreeComponent& OwnerComp)
{
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

		//타겟 발견시 타이머 없애기
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	//플레이어가 주변에 없으면 Player추적 종료
	else {
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		Monster->SetActorTickInterval(0.5f);
		
	}

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), Info.TraceDistance, 20,
		DrawColor, false, 0.3f);
#endif
}

//주변에 적이 없을시 2초 후에 target set to null하기
void UBTService_DetectTarget::ClearTimerAndSetInterval()
{
	if(!CachedOwnerComp)return;
	AAIController* Controller = Cast<AMonsterAIController>(CachedOwnerComp->GetAIOwner());
	if (!Controller)return;	
	
	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if (!Monster)return;

	Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	UE_LOG(LogTemp, Display, TEXT("Target set to null after 2 seconds"));
	Monster->SetActorTickInterval(0.5f);
}
