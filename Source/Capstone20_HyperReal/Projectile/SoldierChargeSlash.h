// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\GameInfo.h"
#include "ProjectileBase.h"
#include "SoldierChargeSlash.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ASoldierChargeSlash : public AProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASoldierChargeSlash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SlashBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
