// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MonsterPoolManager.generated.h"

class AMonster;
class UMonsterObjectPool;

UCLASS()
class CAPSTONE20_HYPERREAL_API UMonsterPoolManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<TSubclassOf<AMonster>, UMonsterObjectPool*> PoolMap;

	UPROPERTY()
	TObjectPtr<UWorld> WorldContext;

public:
	void Initialize(UWorld* World);
	void AddPool(const TSubclassOf<AMonster> MonsterClass, const int32 PoolSize);
	AMonster* GetPooledMonster(const TSubclassOf<AMonster> MonsterClass, const FVector& SpawnLocation, const FRotator& SpawnRotation);
	void ReturnMonsterToPool(AMonster* Monster);
};
