// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBuilding.h"
#include "../Character/PlayerCharacter.h"
#include "BossAttack.h"

ABossBuilding::ABossBuilding()
{
	mDataTableKey = "BossBuilding";
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Low_Poly_Viking_World/Models/Constructions/SM_Small_House_03_A.SM_Small_House_03_A'"));
	if (BuildingMeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(BuildingMeshAsset.Object);
	}
	mMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	mMesh->bReceivesDecals = false;

	//bossattack소환할 주기
	mAttackTime = -1.f;
	mAccAttackTime = 0.f;
	
	//bossattack설정용
	mDecalAdjustTime = -1.f;
	mAttackWaitTime = -1.f;
}

void ABossBuilding::BeginPlay()
{
	Super::BeginPlay();
}

float ABossBuilding::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
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
			mMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		}
	}

	return Damage;
}

void ABossBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!mbIsActivated) return;
	mAccAttackTime+=DeltaTime;
	if(mAttackTime != -1.f && mAccAttackTime >= mAttackTime)
	{
		mAccAttackTime = 0.f;
		
		//player를 찾음
		APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if(!IsValid(Player)) return;
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ABossAttack* AttackActor = GetWorld()->SpawnActor<ABossAttack>(Player->GetActorLocation(), GetActorRotation(), param);
		if(!IsValid(AttackActor)) return;
		AttackActor->SetDamage(mInfo.Attack);
		AttackActor->SetDecalAdjustTime(mDecalAdjustTime);
		AttackActor->SetAttackWaitTime(mAttackWaitTime);
		
	}
	
}
