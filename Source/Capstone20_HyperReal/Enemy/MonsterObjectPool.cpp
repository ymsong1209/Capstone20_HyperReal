// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterObjectPool.h"
#include "Monster.h"

void UMonsterObjectPool::InitializePool(UWorld* World, TSubclassOf<AMonster> InClass, int32 PoolSize)
{
	if (!World || !InClass) return;

	WorldContext = World;
	MonsterClass = InClass;
	InitialPoolSize = PoolSize;
	DefaultSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 풀에 미리 오브젝트 생성하여 저장
	for (int32 i = 0; i < InitialPoolSize; i++)
	{
		AMonster* NewMonster = CreateNewMonsterInPool(FVector::ZeroVector, FRotator::ZeroRotator, DefaultSpawnParams);
		if (NewMonster)
		{
			DisableMonster(NewMonster);
			AvailableMonsters.Enqueue(NewMonster);
			AllMonsters.Add(NewMonster);
		}
	}
}



AMonster* UMonsterObjectPool::GetPooledMonster(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	
	AMonster* Monster = nullptr;
	//사용가능한 몬스터를 Queue에서 반환
	if (!AvailableMonsters.Dequeue(Monster))
	{
		// 풀에 남은 오브젝트가 없으면 새로 생성
		Monster = CreateNewMonsterInPool(SpawnLocation, SpawnRotation, DefaultSpawnParams);
	}
	
	if (Monster)
	{
		InitializeMonster(Monster, SpawnLocation, SpawnRotation);
	}

	return Monster;
}

void UMonsterObjectPool::ReturnMonsterToPool(AMonster* Monster)
{
	if (Monster)
	{
		DisableMonster(Monster);
		AvailableMonsters.Enqueue(Monster); //큐에 몬스터 반납
	}
}



AMonster* UMonsterObjectPool::CreateNewMonsterInPool(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FActorSpawnParameters& SpawnParams)
{
	if (WorldContext && MonsterClass)
	{
		AMonster* Monster = WorldContext->SpawnActor<AMonster>(MonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (Monster)
		{
			AllMonsters.Add(Monster);
		}
		return Monster;
	}
	return nullptr;
}


void UMonsterObjectPool::InitializeMonster(AMonster* Monster, const FVector& SpawnLocation, const FRotator& SpawnRotation) const
{
	Monster->SetActorHiddenInGame(false);
	Monster->SetActorLocation(SpawnLocation);
	Monster->SetActorRotation(SpawnRotation);
	Monster->SetActorEnableCollision(true);
	Monster->SetActorTickEnabled(true);
	Monster->GetMesh()->SetSimulatePhysics(true);
	Monster->GetCharacterMovement()->GravityScale = 1.f;
	Monster->OnPoolMonsterSpawned();
}

void UMonsterObjectPool::DisableMonster(AMonster* Monster) const
{
	Monster->SetActorHiddenInGame(true);
	Monster->SetActorEnableCollision(false);
	Monster->SetActorTickEnabled(false);
	Monster->GetMesh()->SetSimulatePhysics(false);
	Monster->GetCharacterMovement()->GravityScale = 0.f;
}
