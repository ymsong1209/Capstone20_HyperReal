// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StartWidget.h"
#include "GameFramework/GameModeBase.h"
#include "KHIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AKHIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKHIGameModeBase();
private:
	TSubclassOf<UStartWidget> mStartWidgetClass;
	UStartWidget* mStartWidget;
protected:
	virtual void BeginPlay() override;
	
};
