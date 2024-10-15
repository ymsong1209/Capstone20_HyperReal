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

	//블랙보드지정
	if (mAIBlackboard) {
		UBlackboardComponent* BlackboardComp = Blackboard.Get();
		UseBlackboard(mAIBlackboard, BlackboardComp);
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Player) {
			BlackboardComp->SetValueAsObject(TEXT("Target"), Player);
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("no player"));
		}
	}
	
	//행동트리 동작

	if (mAITree) {
		if (!RunBehaviorTree(mAITree)) {
			//예외처리

		}
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
