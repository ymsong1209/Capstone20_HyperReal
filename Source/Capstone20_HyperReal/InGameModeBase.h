// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

class UInGameUserWidget;
class AMonster;
class UMonsterPoolManager;

UCLASS()
class CAPSTONE20_HYPERREAL_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()	
public:
	AInGameModeBase();
	virtual void Tick(float DeltaTime) override;
	AMonster* GetPooledMonster(TSubclassOf<AMonster> MonsterClass, const FVector& SpawnLocation, const FRotator& SpawnRotation);
	void ReturnMonsterToPool(AMonster* Monster);

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TSubclassOf<UInGameUserWidget>	mInGameWidgetClass;

	UPROPERTY()
	TObjectPtr<UInGameUserWidget> mInGameWidget;

	UPROPERTY()
	TObjectPtr<UMonsterPoolManager> mMonsterPoolManager;

	UPROPERTY(EditAnywhere, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	int32 mInitialMonsterPoolSize = 30;

	UPROPERTY(EditAnywhere, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMonster>> MonsterClasses;

public:
	FORCEINLINE UInGameUserWidget* GetInGameWidget() const { return mInGameWidget; }
	

};
