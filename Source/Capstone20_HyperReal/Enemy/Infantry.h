// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Monster.h"
#include "Infantry.generated.h"

/**
 * 기본 보병 클래스
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AInfantry : public AMonster
{
	GENERATED_BODY()
private:
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mWeaponR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mWeaponL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mShield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mBackpack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mHead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infantry")
	class UInfantryShell* mInfantryShell;
	
	
public:
	// Sets default values for this character's properties
	AInfantry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// SwordMan은 피격 애니메이션이 존재
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// GetMesh 함수 재정의
	
public:
	virtual void Attack() override;
	
	
};
