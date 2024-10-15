// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/SaveGame.h"
#include "LevelSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ULevelSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	ULevelSaveGame();
	
	UPROPERTY(BlueprintReadWrite,SaveGame)
	int32 curlevel;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	int32 mainBuildingCurHP;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	int32 mainBuildingMaxHP;
};
