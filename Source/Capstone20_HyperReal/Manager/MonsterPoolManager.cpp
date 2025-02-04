// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPoolManager.h"
#include "../Enemy/MonsterObjectPool.h"
#include "../Enemy/Monster.h"

void UMonsterPoolManager::Initialize(UWorld* World)
{
	WorldContext = World;
}

void UMonsterPoolManager::AddPool(TSubclassOf<AMonster> MonsterClass, int32 PoolSize)
{
	if (!WorldContext || !MonsterClass || PoolMap.Contains(MonsterClass)) return;

	UMonsterObjectPool* NewPool = NewObject<UMonsterObjectPool>();
	if (NewPool)
	{
		NewPool->InitializePool(WorldContext, MonsterClass, PoolSize);
		PoolMap.Add(MonsterClass, NewPool);
	}
}

AMonster* UMonsterPoolManager::GetPooledMonster(TSubclassOf<AMonster> MonsterClass, FVector SpawnLocation,
	FRotator SpawnRotation)
{
	if (PoolMap.Contains(MonsterClass))
	{
		return PoolMap[MonsterClass]->GetPooledMonster(SpawnLocation, SpawnRotation);
	}

	return nullptr;
}

void UMonsterPoolManager::ReturnMonsterToPool(AMonster* Monster)
{
	for (auto& PoolPair : PoolMap)
	{
		if (Monster->IsA(PoolPair.Key))
		{
			PoolPair.Value->ReturnMonsterToPool(Monster);
			return;
		}
	}
}
