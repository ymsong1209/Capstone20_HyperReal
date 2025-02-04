// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterObjectPool.h"
#include "../Enemy/Monster.h"

void UMonsterObjectPool::InitializePool(UWorld* World, TSubclassOf<AMonster> InClass, int32 PoolSize)
{
	if (!World || !InClass) return;

	WorldContext = World;
	MonsterClass = InClass;
	InitialPoolSize = PoolSize;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;  // 충돌 시 자동 조정

	// 풀에 미리 오브젝트 생성하여 저장
	for (int32 i = 0; i < InitialPoolSize; i++)
	{
		AMonster* NewMonster = World->SpawnActor<AMonster>(MonsterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewMonster)
		{
			NewMonster->SetActorHiddenInGame(true);
			NewMonster->SetActorEnableCollision(false);
			NewMonster->SetActorTickEnabled(false);
			NewMonster->GetMesh()->SetSimulatePhysics(false);
			NewMonster->GetCharacterMovement()->GravityScale = 0.f;
			NewMonster->SetMonsterInfo();
			Pool.Add(NewMonster);
		}
	}
}

AMonster* UMonsterObjectPool::GetPooledMonster(FVector SpawnLocation, FRotator SpawnRotation)
{
	for (AMonster* Monster : Pool)
	{
		if (Monster && Monster->IsHidden()) // 비활성화된 오브젝트 찾기
		{
			Monster->SetActorLocation(SpawnLocation);
			Monster->SetActorRotation(SpawnRotation);
			Monster->SetActorHiddenInGame(false);
			Monster->SetActorEnableCollision(true);
			Monster->SetActorTickEnabled(true);
			Monster->GetMesh()->SetSimulatePhysics(true);
			Monster->GetCharacterMovement()->GravityScale = 1.f;
			Monster->OnPoolMonsterSpawned();
			return Monster;
		}
	}

	// 풀에 남은 오브젝트가 없으면 새로 생성
	if (WorldContext && MonsterClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;  // 충돌 시 자동 조정
		
		AMonster* NewMonster = WorldContext->SpawnActor<AMonster>(MonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (NewMonster)
		{
			return NewMonster;
		}
	}

	return nullptr;
}

void UMonsterObjectPool::ReturnMonsterToPool(AMonster* Monster)
{
	if (Monster)
	{
		Monster->SetActorHiddenInGame(true);
		Monster->SetActorEnableCollision(false);
		Monster->SetActorTickEnabled(false);
		Pool.Add(Monster);
	}
}
