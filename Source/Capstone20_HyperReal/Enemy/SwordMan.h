// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "SwordMan.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ASwordMan : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordMan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// SwordMan은 피격 애니메이션이 존재
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	virtual void Attack() override;
	
};
