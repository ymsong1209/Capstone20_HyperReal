// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"

#include "BTTask_Trace.h"
#include "../Enemy/Monster.h"
#include "../Enemy/MonsterAIController.h"
#include "../Enemy/MonsterAnimInstance.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result =  Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target) {
		Monster->GetBodyAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
		if(Monster->GetHeadAnimInstance()) Monster->GetHeadAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
		OwnerComp.GetAIOwner()->StopMovement();
		return EBTNodeResult::Succeeded;
	}

	//몬스터와 target의 위치를 얻어옴
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();
	//몬스터가 타겟을 바라보게 함
	FVector Dir = TargetLoc - MonsterLoc;
	Dir.Normalize();
	Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		
	Monster->GetBodyAnimInstance()->ChangeAnimType(EMonsterAnim::Attack);
	if(Monster->GetHeadAnimInstance()) Monster->GetHeadAnimInstance()->ChangeAnimType(EMonsterAnim::Attack);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	// AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	// Monster->GetAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
	// OwnerComp.GetAIOwner()->StopMovement();
	return result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory,DeltaSeconds);
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Monster) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target) {
		Monster->GetBodyAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
		if(Monster->GetHeadAnimInstance()) Monster->GetHeadAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//몬스터와 target의 위치를 얻어옴
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	//두 위치의 높이를 맞춰줌
	MonsterLoc.Z = TargetLoc.Z;

	//두 위치 사이의 거리를 구함
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	//공격이 끝났을 경우
	if(Monster->GetAttackEnd())
	{
		//공격 범위를 벗어나면 failed return
		if (Distance > Monster->GetMonsterInfo().AttackDistance) {
			Monster->GetBodyAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
			if(Monster->GetHeadAnimInstance()) Monster->GetHeadAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			//몬스터가 타겟을 바라보게 함
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();
			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
			Monster->GetBodyAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
			if(Monster->GetHeadAnimInstance()) Monster->GetHeadAnimInstance()->ChangeAnimType(EMonsterAnim::Idle);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	Monster->SetAttackEnd(false);
	
}

