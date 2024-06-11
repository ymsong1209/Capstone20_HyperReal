// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseLevelGameModeBase.generated.h"

/**
 * 
 */
class UBaseLevelWidget;
UCLASS()
class CAPSTONE20_HYPERREAL_API ABaseLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABaseLevelGameModeBase();
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	TSubclassOf<UBaseLevelWidget>	mBaseLevelWidgetClass;
	UBaseLevelWidget* mBaseLevelWidget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UBaseLevelWidget* GetUBaseLevelWidget() { return mBaseLevelWidget; }
	
};
