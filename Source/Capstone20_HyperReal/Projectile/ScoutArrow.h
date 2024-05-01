// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileBase.h"
#include "ScoutArrow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AScoutArrow : public AProjectileBase
{
	GENERATED_BODY()

public:
	AScoutArrow();
protected:
	virtual void BeginPlay() override;
public:
	virtual  void Tick(float DeltaSeconds) override;

protected:
	virtual void ProjectileStop(const FHitResult& ImpactResult) override;
	virtual void ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity) override;
};
