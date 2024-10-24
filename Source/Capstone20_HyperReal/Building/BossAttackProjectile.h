// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../Projectile/ProjectileBase.h"
#include "BossAttackProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ABossAttackProjectile : public AProjectileBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundCue* mHitSound;
public:
	ABossAttackProjectile();
protected:
	virtual void BeginPlay() override;
public:
	virtual  void Tick(float DeltaSeconds) override;

protected:
	virtual void ProjectileStop(const FHitResult& ImpactResult) override;
	virtual void ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity) override;
	
};
