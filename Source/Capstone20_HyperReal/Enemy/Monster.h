// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Monster.generated.h"

enum class EMonsterAnim : uint8;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UMonsterAnimInstance*> AnimInstances;
	
	class AMonsterAIController* mAIController;

	//몬스터를 특정 위치에서 소환하고 싶은 경우
	class AMonsterSpawnPoint* mSpawnPoint;

	class ABuilding* mBuilding;

	FString mDataTableKey;

	bool mAttackEnd;
	bool bIsInvincible;
	bool bCanAttack;

	//에어본 시킬 수 있는 몬스터인지
	bool  bCanAirborne;
	//에어본 상태인지
	bool  bIsAirborne;

private:
	float fAirborneTime;
	float fMaxAirborneTime;
	float fInitialZ;
public:
	bool GetAttackEnd() const { return mAttackEnd; }
	TArray<class UMonsterAnimInstance*> GetAnimInstances() const { return AnimInstances; }
	void SetAnimation(EMonsterAnim AnimType);
	const FMonsterInfo& GetMonsterInfo() const { return mInfo; }
	void SetSpawnPoint(class AMonsterSpawnPoint* Point) { mSpawnPoint = Point; }
	void SetOwnerBuilding(class ABuilding* Building) { mBuilding = Building; }
	ABuilding* GetOwnerBuilding() { return mBuilding; }
	void SetAttackEnd(bool End) { mAttackEnd = End; }

	void SetCanAttack(bool _attack){bCanAttack = _attack;}
	bool GetCanAttack(){return bCanAttack;}
	void SetHPBar(float fRate);

	AMonsterAIController* GetAIController() const {return mAIController;}

	void SetMonsterInfo();

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
	
private:
	void HandleHitAnimation(FDamageEvent const& DamageEvent);
	void StartAirborne();

public:
	virtual void Attack();
};
