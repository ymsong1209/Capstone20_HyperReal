// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "UObject/NoExportTypes.h"
#include "GameData.h"

#include "GameInfo.generated.h"

UENUM(BlueprintType)
enum class EPlayerSkill : uint8
{
	SkillA UMETA(DisplayName = "SkillA"),
	SkillS UMETA(DisplayName = "SkillS"),
	SkillD UMETA(DisplayName = "SkillD"),
	SkillF UMETA(DisplayName = "SkillF"),
	None UMETA(DisplayName = "None")
};

UCLASS()
class CAPSTONE20_HYPERREAL_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
