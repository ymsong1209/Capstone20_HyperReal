// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
void UInGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInGameUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCharacterHUD = Cast<UCharacterHUDWidget>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	skillicon = Cast<UImage>(GetWidgetFromName(TEXT("skillicon1")));
	//if (skillicon)
	//{
	//	skillicon->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"),0.2f);
	//}
}

void UInGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGameUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
void UInGameUserWidget::SetHP(int32 HP, int32 HPMax)
{
	mCharacterHUD->SetHPPercent(HP / (float)HPMax);

}
