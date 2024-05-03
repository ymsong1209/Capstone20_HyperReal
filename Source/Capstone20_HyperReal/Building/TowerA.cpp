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
	//���� ������ ���
	if (Damage == -1.f)
		return Damage;
	
	while (mCurPhase < mInfo.PhaseTriggerHP.Num() && mInfo.HP <= mInfo.PhaseTriggerHP[mCurPhase])
	{
		mInfo.SpawnIntervalSeconds -= 1.f; // ��ȭ ����, ���� ��� ���� ������ ����
		++mCurPhase; // ���� �ܰ�� �̵�
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
