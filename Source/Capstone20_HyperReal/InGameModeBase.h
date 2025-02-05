// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

class UInGameUserWidget;
class AMonster;

UCLASS()
class CAPSTONE20_HYPERREAL_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	TSubclassOf<UInGameUserWidget>	mInGameWidgetClass;
	UInGameUserWidget* mInGameWidget;

	UPROPERTY()
	class UMonsterPoolManager* mMonsterPoolManager;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	int32 mInitialMonsterPoolSize = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	TArray<TSubclassOf<AMonster>> MonsterClasses;


	

public:
	UInGameUserWidget* GetInGameWidget() { return mInGameWidget;}
	
	AMonster* GetPooledMonster(TSubclassOf<AMonster> MonsterClass, FVector SpawnLocation, FRotator SpawnRotation);
	void ReturnMonsterToPool(AMonster* Monster);
	
public:
	AInGameModeBase();

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
