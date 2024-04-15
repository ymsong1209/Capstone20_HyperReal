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
		skillicon->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), 0.4f);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("skillicon does not have a dynamic material"));
	}
}
void UInGameUserWidget::SetHP(int32 HP, int32 HPMax)
{
	mCharacterHUD->SetHPPercent(HP / (float)HPMax);

}
