// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/SaveGame.h"
#include "PlayerUpgradeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UPlayerUpgradeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPlayerUpgradeSaveGame();

	UPROPERTY(BlueprintReadWrite, Category = "Player Stats")
	FPlayerInfo m_fPlayerInfo;

	UPROPERTY(BlueprintReadWrite, Category = "Rune Level")
	TArray<int32> m_arrRuneLevels;
};
