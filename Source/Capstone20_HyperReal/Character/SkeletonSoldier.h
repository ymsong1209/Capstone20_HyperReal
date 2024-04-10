// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "SkeletonSoldier.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ASkeletonSoldier : public APlayerCharacter
{
	GENERATED_BODY()
	
	ASkeletonSoldier();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UStaticMeshComponent* RWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack();
};
