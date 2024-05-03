// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerCharacter.h"
#include "SkeletonSoldier.generated.h"


class AWeapon;

UCLASS()
class CAPSTONE20_HYPERREAL_API ASkeletonSoldier : public APlayerCharacter
{
	GENERATED_BODY()

	ASkeletonSoldier();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* m_ChargingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* m_ChargeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* m_WhirlWindMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* m_LeapAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* m_UndeadFuryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fChargingTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fWhilrwindDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fWhildWindSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fLeapMaxDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UMaterialInterface* m_pLeapAttackRangeDecalInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UMaterialInterface* m_pLeapAttackDecalInterface;

private:
	float m_fChargeStartTime;
	int32 m_iChargeAttackCount;
	int32 m_iAccChargeAttackCount;

	FTimerHandle m_hWhirlwindHandle;
	FTimerHandle m_hUndeadFuryHandle;

	class AWeapon* m_pRWeapon;

	FVector m_vLeapAttackPos;
	bool m_bOnLeapAttackCharge;

	UDecalComponent* m_pLeapAttackDecal;

private:
	// Leap 공격 범위용 데칼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* m_pLeapAttackRangeDecal;

public:
	int32 GetChargeAttackCount() { return m_iChargeAttackCount; }
	AWeapon* GetRWeapon() { return m_pRWeapon; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Attack() override;
	virtual void SkillEnd() override;

private:
	// 차지 공격
	void ChargeStart();
	void Charging();
	void ChargeAttack();

	// 훨윈드
	void Whirlwind();

	// 리프 어택
	void LeapAttack();

	// 언데드 퓨리
	void UndeadFury();
	void UndeadFuryBuffEnd();

public:
	void ChargeAttackEnd();
	void WhirlwindEnd();
	void LeapAttackMove();

	void EjectChargeSlash();

public:
	//건물 상호작용 테스트 코드
	void TestBuildingSpawn();
};
