// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Monster.h"
#include "Scout.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AScout : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AScout();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
