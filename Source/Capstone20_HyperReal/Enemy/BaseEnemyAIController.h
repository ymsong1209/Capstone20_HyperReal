// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200;
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	
};
