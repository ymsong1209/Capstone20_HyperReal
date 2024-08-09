// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BossAttack.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API ABossAttack : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BossAttack")
	float mDecalAdjustTime; //일정시간동안 데칼 크기 늘렸다가 줄이면서 플레이어 추적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BossAttack")
	float mAttackWaitTime; //DecalAdjusttime시간이 지난후, 일정 시간 대기 후 공격

	float mAccDecalAdjustTime;
	float mAccAttackTime;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossAttack")
	UDecalComponent* mDecal;

	float mDamage;
public:
	void SetDecalAdjustTime(float time){mDecalAdjustTime = time;}
	void SetAttackWaitTime(float time){mAttackWaitTime = time;}
	void SetDamage(float Damage)
	{
		mDamage = Damage;
	}

private:
	void AdjustDecal(float Deltatime);
	void FollowPlayer();
	void SpawnProjectile();
public:
	// Sets default values for this actor's properties
	ABossAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
