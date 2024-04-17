// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fChargingTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fWhilrwindDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float m_fWhildWindSpeed;

private:
	float m_fChargeStartTime;
	int32 m_iChargeAttackCount;

	FTimerHandle m_hWhirlwindHandle;

	class AWeapon* m_pRWeapon;

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
	virtual void Attack();

private:
	// D 키에 바인딩
	void ChargeStart();
	void Charging();
	void ChargeAttack();

	// A 키에 바인딩
	void Whirlwind();
public:
	void WhirlwindEnd();
};
