// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"



UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	//tick�� 0.5�� +=0.1�� ���̿� �ѹ� �۵���
	Interval = 0.5f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}