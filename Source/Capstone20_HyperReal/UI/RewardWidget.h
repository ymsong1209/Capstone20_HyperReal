// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RewardWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API URewardWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* RewardMoney;
	UTextBlock* DestroyBuildingCount;
	UTextBlock* KillEnemyCount;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void setRewardMoney(int gold);
	void setDestroyBuildingCount(int count);
	void setKillEnemyCount(int count);
};
