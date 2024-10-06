// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	int32 curlevel;
	int32 mainBuildingCurHP;
	int32 mainBuildingMaxHP;
	bool  isLevelClear;

public:
	ULevelManager();
	~ULevelManager();
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Init();

public:
	void LoadInGameLevel();
	int32 GetBuildingHP();
	int32 GetBuildingMaxHP();
	void LevelClear();
	void SetLevelClear(bool _bValue) {_bValue = isLevelClear;};
	
};
