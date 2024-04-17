// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGameUserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "KHIPlayGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AKHIPlayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKHIPlayGameModeBase();	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	TSubclassOf<UInGameUserWidget>	mInGameWidgetClass;
	UInGameUserWidget* mInGameWidget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UInGameUserWidget* GetInGameWidget() {
		return mInGameWidget;
	}
};
