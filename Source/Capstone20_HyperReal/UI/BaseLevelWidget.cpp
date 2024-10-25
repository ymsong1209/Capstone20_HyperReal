// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"

void UBaseLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseLevelWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mBasecampWidget = Cast<UBasecampWidget>(GetWidgetFromName(TEXT("Basecampwidget")));
	mCloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("GameCloseBtn")));
	mCloseBtn->OnClicked.AddDynamic(this, &UBaseLevelWidget::QuitGame);
}

void UBaseLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//mBasecampWidget->SetVisibility(ESlateVisibility::Collapsed);
	mBasecampWidget->SetVisibility(ESlateVisibility::Visible);
	PushWidget(mBasecampWidget);
}

void UBaseLevelWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseLevelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBaseLevelWidget::PushWidget(UMyWidget* widget)
{
	if (widget)
	{
		ActivateWidgets.Add(widget);
	}
}

UMyWidget* UBaseLevelWidget::PopWidget()
{
	if (ActivateWidgets.Num() == 0)
	{
		return nullptr;
	}

	UMyWidget* TopWidget = ActivateWidgets.Last();
	ActivateWidgets.RemoveAt(ActivateWidgets.Num() - 1);

	return TopWidget;
}

UMyWidget* UBaseLevelWidget::TopWidget()
{
	if (ActivateWidgets.Num() == 0)
	{
		return nullptr;
	}

	return ActivateWidgets.Last();
}

void UBaseLevelWidget::CloseUI()
{
	if (ActivateWidgets.Num() == 0)
	{

	}
	else
	{
		UMyWidget* widget = TopWidget();
		PopWidget();
		widget->CloseUI();
	}
}

void UBaseLevelWidget::OpenUI()
{
	//mBasecampWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBaseLevelWidget::QuitGame()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		GameInst->SavePlayerData();
		GameInst->SaveLevelData();
	}
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UBaseLevelWidget::RefreshBaseCampMagicWidget()
{
	if (mBasecampWidget)
	{
		mBasecampWidget->RefreshMagicWidget();
	}
}
