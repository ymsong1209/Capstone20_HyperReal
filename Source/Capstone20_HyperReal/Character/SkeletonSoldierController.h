// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickMoveController.h"
#include "SkeletonSoldierController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API ASkeletonSoldierController : public AClickMoveController
{
	GENERATED_BODY()
	
public:
	ASkeletonSoldierController();

protected:
	virtual void OnClickMoveTriggered() override;
	virtual void OnClickMoveReleased() override;
};
