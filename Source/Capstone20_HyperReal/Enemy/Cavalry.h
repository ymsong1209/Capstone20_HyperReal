// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Monster.h"
#include "Cavalry.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ACavalry : public AMonster
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mWeaponR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mWeaponL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mQuiver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	mShield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mHead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mBody;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponRMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponLMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mQuiverMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mShieldMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mHorseMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mHeadMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mBodyMeshes;
public:
	// Sets default values for this character's properties
	ACavalry();

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
