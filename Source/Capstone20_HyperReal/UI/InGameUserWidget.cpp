// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Image.h"
#include "Materials/Material.h"
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
	if (skillicon && skillicon->GetDynamicMaterial()) {
		UE_LOG(LogTemp, Display, TEXT("dynamiccalled"));
		rate += InDeltaTime * 0.6f;
		if (rate >= 1.f)
			rate = 0;
		skillicon->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("skillicon does not have a dynamic material"));
	}
}
void UInGameUserWidget::SetHP(int32 HP, int32 HPMax)
{
	mCharacterHUD->SetHPPercent(HP / (float)HPMax);
}

void UInGameUserWidget::Skill1CoolTime(float frate)
{
	if (skillicon && skillicon->GetDynamicMaterial()) 
	{
		skillicon->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), frate);
	}
}
