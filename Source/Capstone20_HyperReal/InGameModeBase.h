// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

class UInGameUserWidget;
UCLASS()
class CAPSTONE20_HYPERREAL_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AInGameModeBase();

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	TSubclassOf<UInGameUserWidget>	mInGameWidgetClass;
	UInGameUserWidget* mInGameWidget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UInGameUserWidget* GetInGameWidget() { return mInGameWidget; }
};
