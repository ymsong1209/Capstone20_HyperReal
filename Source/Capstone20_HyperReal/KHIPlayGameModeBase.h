// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KHIPlayGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AKHIPlayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKHIPlayGameModeBase();	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
