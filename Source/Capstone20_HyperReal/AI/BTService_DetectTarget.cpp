// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"



UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("Detect");
	//tick이 0.5초 +=0.1초 사이에 한번 작동됨
	Interval = 0.5f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}