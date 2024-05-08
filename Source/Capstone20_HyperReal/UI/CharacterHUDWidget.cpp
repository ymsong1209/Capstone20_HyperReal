// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUDWidget.h"
void UCharacterHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCharacterHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar2")));
	mSPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SPBar2")));
	int a = 0;
}

void UCharacterHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

