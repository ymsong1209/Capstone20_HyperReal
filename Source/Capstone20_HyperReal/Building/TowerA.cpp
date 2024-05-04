// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerA.h"

ATowerA::ATowerA()
{
	mDataTableKey = "TowerA";
}

void ATowerA::BeginPlay()
{
	Super::BeginPlay();
}

float ATowerA::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//무적 상태인 경우
	if (Damage == -1.f)
		return Damage;
	
	while (mCurPhase < mInfo.PhaseTriggerHP.Num() && mInfo.HP <= mInfo.PhaseTriggerHP[mCurPhase])
	{
		mInfo.SpawnIntervalSeconds -= 1.f; // 강화 실행, 예를 들어 스폰 간격을 감소
		++mCurPhase; // 다음 단계로 이동
		if (mCurPhase < mMeshes.Num() && mMeshes[mCurPhase])
		{
			mMesh->SetStaticMesh(mMeshes[mCurPhase]);
		}
	}

	return Damage;
}

void ATowerA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
