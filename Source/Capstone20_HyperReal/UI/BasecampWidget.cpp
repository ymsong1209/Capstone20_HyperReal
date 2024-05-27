// Fill out your copyright notice in the Description page of Project Settings.


#include "BasecampWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
void UBasecampWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBasecampWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//UpgradeWidget = Cast<UCharacterHUDWidget>(GetWidgetFromName(TEXT("UpgradeWidget")));
	//MagicWidget = Cast<URewardWidget>(GetWidgetFromName(TEXT("MagicWidget")));
	//MaintainWidget = Cast<UBasecampWidget>(GetWidgetFromName(TEXT("MaintainWidget")));

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
	//UpgradeWidget->SetVisibility(ESlateVisibility::Collapsed);
	//MagicWidget->SetVisibility(ESlateVisibility::Collapsed);
	//MaintainWidget->SetVisibility(ESlateVisibility::Collapsed);
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
		MaintainWidget->SetVisibility(ESlateVisibility::Visible);
		AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
		if (GameMode)
		{
			UInGameUserWidget* widget = GameMode->GetInGameWidget();
			if (widget && widget->IsVisible())
			{
				//widget->PushWidget(UpgradeWidget);
			}
		}
	}
	
}

void UBasecampWidget::MagicButtonClick()
{
	if (MagicWidget)
	{
		MaintainWidget->SetVisibility(ESlateVisibility::Visible);
		AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
		if (GameMode)
		{
			UInGameUserWidget* widget = GameMode->GetInGameWidget();
			if (widget && widget->IsVisible())
			{
				//widget->PushWidget(MagicWidget);
			}
		}
	}
}

void UBasecampWidget::MaintainButtonClick()
{
	if (MaintainWidget)
	{
		MaintainWidget->SetVisibility(ESlateVisibility::Visible);
		AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
		if (GameMode)
		{
			UInGameUserWidget* widget = GameMode->GetInGameWidget();
			if (widget && widget->IsVisible())
			{
				//widget->PushWidget(MaintainWidget);
			}
		}
	}
}

void UBasecampWidget::NextStageButtonClick()
{
	//여기서 다음 레벨로 이동;
}

void UBasecampWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
	//pause풀고 다음씬 이동
}
