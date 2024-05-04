// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "Monster.h"


// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

	mSpawnMonster = nullptr;
	mSpawnTimeAcc = 0.f;

	//mSpawnTime이 -1.f일 경우 한번만 spawn
	mSpawnTime = -1.f;
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	//처음에는 몬스터 생성
	if (IsValid(mMonsterClass)) {

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		mSpawnMonster = GetWorld()->SpawnActor<AMonster>(mMonsterClass, GetActorLocation(), GetActorRotation(), param);

		//생성된 몬스터에게 spawnpoint알려줌
		mSpawnMonster->SetSpawnPoint(this);
	}


}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//몬스터가 죽었을 경우 계속해서 Spawn 처리를 해주어야 할 경우
	if (mSpawnTime > -1.f) {

		//몬스터가 죽었는지 판단.
		if (mSpawnMonster == nullptr) {
			mSpawnTimeAcc += DeltaTime;
			if (mSpawnTimeAcc >= mSpawnTime) {
				mSpawnTimeAcc = 0.f;

				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				mSpawnMonster = GetWorld()->SpawnActor<AMonster>(mMonsterClass, GetActorLocation(), GetActorRotation(), param);

				//생성된 몬스터에게 spawnpoint알려줌
				mSpawnMonster->SetSpawnPoint(this);
			}
		}
	}
}

