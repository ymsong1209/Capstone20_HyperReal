// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MonsterObjectPool.generated.h"

/**
 * 
 */
class AMonster;
UCLASS()
class CAPSTONE20_HYPERREAL_API UMonsterObjectPool : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<AMonster*> Pool;  // 풀에 저장된 오브젝트 리스트
	TSubclassOf<AMonster> MonsterClass; // 생성할 오브젝트 클래스
	UWorld* WorldContext;
	int32 InitialPoolSize;

public:
	
	void InitializePool(UWorld* World, TSubclassOf<AMonster> InClass, int32 PoolSize);
	
	AMonster* GetPooledMonster(FVector SpawnLocation, FRotator SpawnRotation);
	
	void ReturnMonsterToPool(AMonster* Monster);
};
