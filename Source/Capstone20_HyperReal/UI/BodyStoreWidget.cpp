// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyStoreWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
void UBodyStoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBodyStoreWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	backButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton123")));

	MyMoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyMoney")));;
	UpgradeButton = Cast<UButton>(GetWidgetFromName(TEXT("PlusButton")));;
	progressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progress")));;
	UpgradeCostCurText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeCurCost")));;
	UpgradeCostMaxText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeMaxCost")));;



	backButton->OnClicked.AddDynamic(this, &UBodyStoreWidget::CloseButtonUI);
	UpgradeButton->OnClicked.AddDynamic(this, &UBodyStoreWidget::Upgrade);
}

void UBodyStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MyMoneyText->SetText(FText::FromString(TEXT("1200")));
	UpgradeCostCurText->SetText(FText::FromString(TEXT("100")));
	UpgradeCostMaxText->SetText(FText::FromString(TEXT("200")));
	progressBar->SetPercent(0.5f);
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
	AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
	if (GameMode)
	{
		UInGameUserWidget* widget = GameMode->GetInGameWidget();
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
