// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "CapStoneGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UCapStoneGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UDataTable* mPlayerInfoTable;

	UPROPERTY()
	UDataTable* mMonsterInfoTable;

	UPROPERTY()
	UDataTable* mBuildingInfoTable;

public:
	const FMonsterDataTableInfo* FindMonsterInfo(const FString& _Name);
	const FPlayerDataTableInfo* FindPlayerInfo(const FString& _Name);
	const FBuildingDataTableInfo* FindBuildingInfo(const FString& _Name);
public:
	virtual void Init();

public:
	UCapStoneGameInstance();
};
