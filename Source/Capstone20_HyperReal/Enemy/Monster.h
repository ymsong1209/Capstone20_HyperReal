// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Capstone20_HyperReal/CapStoneGameInstance.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Monster.generated.h"


enum class EMonsterAnim : uint8;

class ABuilding;
class AMonsterSpawnPoint;
class UMonsterAnimInstance;
class AMonsterAIController;

UCLASS()
class CAPSTONE20_HYPERREAL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Attack() {};
	void HandleDeath();
	void DeathEnd();
	virtual void OnPoolMonsterSpawned();
	
	
	

protected:
	virtual void BeginPlay() override;
	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere)
	FMonsterInfo mInfo;
	
	
	UPROPERTY(EditAnywhere)
	TArray<UMonsterAnimInstance*> AnimInstances;

	UPROPERTY()
	TObjectPtr<AMonsterAIController> mAIController;

	//몬스터를 특정 위치에서 소환하고 싶은 경우
	UPROPERTY()
	TObjectPtr<AMonsterSpawnPoint> mSpawnPoint;

	UPROPERTY()
	TObjectPtr<ABuilding> mBuilding;

	FString mDataTableKey;

	bool  bCanAirborne;

private:
	void SetMonsterInfo();
	void SetHPBar(const float fRate);
	void HandleHitAnimation(FDamageEvent const& DamageEvent);
	void StartAirborne();
	void HandleAirborne(float DeltaTime);

	void AddGoldToPlayer(UCapStoneGameInstance* GameInst) const;
	void AddGoldToUI(UCapStoneGameInstance* GameInst) const;

	bool  bCanAttack;
	bool mAttackEnd;
	bool bIsInvincible;

	
	bool  bIsAirborne;
	float fAirborneTime;
	float fMaxAirborneTime;
	float fAirborneStartZ;
public:
	TArray<UMonsterAnimInstance*> GetAnimInstances() const { return AnimInstances; }
	void SetAnimation(EMonsterAnim AnimType);
	FORCEINLINE const FMonsterInfo& GetMonsterInfo() const { return mInfo; }
	FORCEINLINE void SetSpawnPoint(AMonsterSpawnPoint* Point) { mSpawnPoint = Point; }
	FORCEINLINE void SetOwnerBuilding(ABuilding* Building) { mBuilding = Building; }
	FORCEINLINE bool GetAttackEnd() const { return mAttackEnd; }
	FORCEINLINE void SetAttackEnd(const bool End) { mAttackEnd = End; }
	FORCEINLINE void SetCanAttack(const bool CanAttack) { bCanAttack = CanAttack; }
	FORCEINLINE bool CanAttack() const { return bCanAttack; }
	FORCEINLINE AMonsterAIController* GetAIController() const { return mAIController; }
};
