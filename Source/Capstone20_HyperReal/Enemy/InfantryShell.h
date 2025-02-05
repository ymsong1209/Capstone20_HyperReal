// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InfantryShell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CAPSTONE20_HYPERREAL_API UInfantryShell : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mBodyMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponRMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponLMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mBackpackMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mHeadMeshes;
};
