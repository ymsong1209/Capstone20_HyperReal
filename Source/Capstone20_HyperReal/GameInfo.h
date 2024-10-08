// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"
#include "UObject/NoExportTypes.h"
#include "GameData.h"
#include "Engine/DamageEvents.h"
#include "GameInfo.generated.h"

UENUM(BlueprintType)
enum class EPlayerSkill : uint8
{
	SkillA UMETA(DisplayName = "SkillA"),
	SkillS UMETA(DisplayName = "SkillS"),
	SkillD UMETA(DisplayName = "SkillD"),
	SkillF UMETA(DisplayName = "SkillF"),
	Dash UMETA(DisplayName = "Dash"),
	None UMETA(DisplayName = "None")
};

UCLASS()
class CAPSTONE20_HYPERREAL_API UGameInfo : public UObject
{
	GENERATED_BODY()
};
