// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Weapon.h"
#include "LongSword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ALongSword : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ALongSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
