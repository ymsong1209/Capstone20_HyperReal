// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Building.h"
#include "TowerA.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ATowerA : public ABuilding
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATowerA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
