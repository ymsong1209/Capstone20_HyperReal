// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyStoreWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../BaseLevelGameModeBase.h"
#include "BaseLevelWidget.h"
void UBodyStoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBodyStoreWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	HP_backButton = Cast<UButton>(GetWidgetFromName(TEXT("BodyBackButton123")));
	//
	HP_MyMoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BodyMyMoney")));;
	HPUpgradeButton = Cast<UButton>(GetWidgetFromName(TEXT("BodyPlusButton")));;
	RestoreprogressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BodyProgress")));;
	UpgradeCostCurText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeCurCost")));;
	UpgradeCostMaxText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeMaxCost")));;
	//
	//
	//
	HP_backButton->OnClicked.AddDynamic(this, &UBodyStoreWidget::CloseButtonUI);
	HPUpgradeButton->OnClicked.AddDynamic(this, &UBodyStoreWidget::Upgrade);
}

void UBodyStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HP_MyMoneyText->SetText(FText::FromString(TEXT("1200")));
	UpgradeCostCurText->SetText(FText::FromString(TEXT("100")));
	UpgradeCostMaxText->SetText(FText::FromString(TEXT("200")));
	RestoreprogressBar->SetPercent(0.5f);
}

void UBodyStoreWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBodyStoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBodyStoreWidget::CloseButtonUI()
{
	ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
	if (GameMode)
	{
		UBaseLevelWidget* widget = GameMode->GetUBaseLevelWidget();
		if (widget)
		{
			widget->CloseUI();
		}
	}
}

void UBodyStoreWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBodyStoreWidget::Upgrade()
{
}
