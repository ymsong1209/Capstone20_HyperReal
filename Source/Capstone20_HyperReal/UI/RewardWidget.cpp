// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardWidget.h"

void URewardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URewardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	RewardMoney = Cast<UTextBlock>(GetWidgetFromName(TEXT("RewardMoneyText")));
	DestroyBuildingCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("DestroyBuildingText")));
	KillEnemyCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillEnemyCountText")));
}

void URewardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URewardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void URewardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URewardWidget::setRewardMoney(int gold)
{
	FString str = "+";
	str += FString::FromInt(gold);
	RewardMoney->SetText(FText::FromString(str));
}

void URewardWidget::setDestroyBuildingCount(int count)
{
	DestroyBuildingCount->SetText(FText::FromString(FString::FromInt(count)));
}

void URewardWidget::setKillEnemyCount(int count)
{
	KillEnemyCount->SetText(FText::FromString(FString::FromInt(count)));
}
