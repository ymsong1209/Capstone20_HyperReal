// Fill out your copyright notice in the Description page of Project Settings.


#include "BasecampWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../BaseLevelGameModeBase.h"
#include "BaseLevelWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
void UBasecampWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBasecampWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpgradeWidget = Cast<UUpgradeWidget>(GetWidgetFromName(TEXT("UpgradeWidget")));
	MagicWidget = Cast<UMagicWidget>(GetWidgetFromName(TEXT("MagicWidget")));
	MaintainWidget = Cast<UBodyStoreWidget>(GetWidgetFromName(TEXT("BodyRestoreWidget")));

	mUpgradeButton = Cast<UButton>(GetWidgetFromName(TEXT("UpgradeButton")));
	mMagicButton = Cast<UButton>(GetWidgetFromName(TEXT("MagicButton")));
	mMaintainButton = Cast<UButton>(GetWidgetFromName(TEXT("MaintainButton")));
	mNextStageButton = Cast<UButton>(GetWidgetFromName(TEXT("NextStageButton")));

	mUpgradeButton->OnClicked.AddDynamic(this, &UBasecampWidget::UpgradeButtonClick);
	mMagicButton->OnClicked.AddDynamic(this, &UBasecampWidget::MagicButtonClick);
	mMaintainButton->OnClicked.AddDynamic(this, &UBasecampWidget::MaintainButtonClick);
	mNextStageButton->OnClicked.AddDynamic(this, &UBasecampWidget::NextStageButtonClick);

}

void UBasecampWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpgradeWidget->SetVisibility(ESlateVisibility::Collapsed);
	MagicWidget->SetVisibility(ESlateVisibility::Collapsed);
	MaintainWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UBasecampWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBasecampWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBasecampWidget::UpgradeButtonClick()
{
	if (UpgradeWidget)
	{
		UpgradeWidget->SetVisibility(ESlateVisibility::Visible);
		ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
		if (GameMode)
		{
			UBaseLevelWidget* widget = GameMode->GetUBaseLevelWidget();
			if (widget && widget->IsVisible())
			{
				widget->PushWidget(UpgradeWidget);
			}
		}
	}
	
}

void UBasecampWidget::MagicButtonClick()
{
	if (MagicWidget)
	{
		MagicWidget->SetVisibility(ESlateVisibility::Visible);
		ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
		if (GameMode)
		{
			UBaseLevelWidget* widget = GameMode->GetUBaseLevelWidget();
			if (widget && widget->IsVisible())
			{
				widget->PushWidget(MagicWidget);
			}
		}
	}
}

void UBasecampWidget::MaintainButtonClick()
{
	if (MaintainWidget)
	{
		MaintainWidget->SetVisibility(ESlateVisibility::Visible);
		ABaseLevelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABaseLevelGameModeBase>();
		if (GameMode)
		{
			UBaseLevelWidget* widget = GameMode->GetUBaseLevelWidget();
			if (widget && widget->IsVisible())
			{
				widget->PushWidget(MaintainWidget);
			}
		}
	}
}

void UBasecampWidget::NextStageButtonClick()
{
	//���⼭ ���� ������ �̵�;
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level1"));
}

void UBasecampWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
	//pauseǮ�� ������ �̵�
}
