// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CavalryShell.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UCavalryShell : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponRMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mWeaponLMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mQuiverMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*>	mShieldMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mHorseMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mHeadMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USkeletalMesh*>	mBodyMeshes;
};
