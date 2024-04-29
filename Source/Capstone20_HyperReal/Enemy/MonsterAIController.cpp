// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"


AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AIAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/A_SYMContent/Monster/BT_Monster.BT_Monster'"));

	if (AIAsset.Succeeded()) {
		mAITree = AIAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackBoardAsset(TEXT("/Script/AIModule.BlackboardData'/Game/A_SYMContent/Monster/BB_Monster.BB_Monster'"));

	if (AIBlackBoardAsset.Succeeded()) {
		mAIBlackboard = AIBlackBoardAsset.Object;
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//����������
	if (mAIBlackboard) {
		UBlackboardComponent* BlackboardComp = Blackboard.Get();
		UseBlackboard(mAIBlackboard, BlackboardComp);
	}
	
	//�ൿƮ�� ����

	if (mAITree) {
		if (!RunBehaviorTree(mAITree)) {
			//����ó��

		}
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
