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
	class ABuilding* mainBuilding;
	int32 mainBuildingCurHP;
	int32 mainBuildingMaxHP;
	bool  isLevelClear;

	int monsterDeathCount;

public:
	ULevelManager();
	~ULevelManager();
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Init();
public:
	void SaveLevelData(USaveGame* _pSaveGame);//세이브 파일에 저장
	void LoadLevelData(USaveGame* _pSaveGame);//세이브 파일에서 불러오기
public:
	void LoadInGameLevel();
	int32 GetBuildingHP();
	int32 GetBuildingMaxHP();
	void SetBuilding(class ABuilding* _building) { mainBuilding = _building; }
	void SetBuildingHP();
	void LevelClear();
	void SetLevelClear(bool _bValue) {_bValue = isLevelClear;};
	void AddMonsterDeathCount(){++monsterDeathCount;}
	int GetMonsterDeathCount() const { return monsterDeathCount; }
	
};
