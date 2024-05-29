// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Infantry.h"
#include "TwoHanded.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ATwoHanded : public AInfantry
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwoHanded();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack() override;
};
