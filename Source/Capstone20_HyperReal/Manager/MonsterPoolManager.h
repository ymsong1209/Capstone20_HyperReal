// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MonsterPoolManager.generated.h"

/**
 * 
 */
class AMonster;

UCLASS()
class CAPSTONE20_HYPERREAL_API UMonsterPoolManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<TSubclassOf<AMonster>, class UMonsterObjectPool*> PoolMap;
	UWorld* WorldContext;

public:
	void Initialize(UWorld* World);
	void AddPool(TSubclassOf<AMonster> MonsterClass, int32 PoolSize);
	AMonster* GetPooledMonster(TSubclassOf<AMonster> MonsterClass, FVector SpawnLocation, FRotator SpawnRotation);
	void ReturnMonsterToPool(AMonster* Monster);
};
