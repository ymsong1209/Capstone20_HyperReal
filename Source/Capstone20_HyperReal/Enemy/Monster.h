// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
//#include "MonsterAnimInstance.h"
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

	FString mDataTableKey;

public:
	class UMonsterAnimInstance* GetAnimInstance() const { return mAnim; }
	
	const FMonsterInfo& GetMonsterInfo() const {
		return mInfo;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* Point) {
		mSpawnPoint = Point;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void Death();
};
