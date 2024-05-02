// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMonsterInfo mInfo;

	class UMonsterAnimInstance* mAnim;

	class AMonsterSpawnPoint* mSpawnPoint;

	class ABuilding* mBuilding;

	FString mDataTableKey;

	bool mAttackEnd;
	bool bIsInvincible;
public:
	bool GetAttackEnd() const
	{
		return mAttackEnd;
	}
	
	class UMonsterAnimInstance* GetAnimInstance() const { return mAnim; }
	
	const FMonsterInfo& GetMonsterInfo() const {
		return mInfo;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* Point) {
		mSpawnPoint = Point;
	}

	void SetOwnerBuilding(class ABuilding* Buliding) {
		mBuilding = Buliding;
	}

	ABuilding* GetOwnerBuilding() {
		return mBuilding;
	}

	void SetAttackEnd(bool End)
	{
		mAttackEnd = End;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void HandleDeath();
	void DeathEnd();

public:
	virtual void Attack();
};
