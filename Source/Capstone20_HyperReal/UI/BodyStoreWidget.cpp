// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyStoreWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../BaseLevelGameModeBase.h"
#include "BaseLevelWidget.h"
#include "../CapStoneGameInstance.h"
#include "../Manager/PlayerManager.h"
#include "../GameData.h"
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
	Refresh();
	
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

void UBodyStoreWidget::Refresh()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
	FString gstr = FString::FromInt(gold);
	HP_MyMoneyText->SetText(FText::FromString(gstr));

	int curHP = GameInst->GetPlayerManager()->GetPlayerInfo().HP;
	int maxHP = GameInst->GetPlayerManager()->GetPlayerInfo().MaxHP;
	FString hstr = FString::FromInt(curHP);
	UpgradeCostCurText->SetText(FText::FromString(hstr));
	hstr = FString::FromInt(maxHP);
	UpgradeCostMaxText->SetText(FText::FromString(hstr));
	RestoreprogressBar->SetPercent((float)curHP / (float)maxHP);
}

void UBodyStoreWidget::Upgrade()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst->GetPlayerManager()->GetPlayerInfo().HP == GameInst->GetPlayerManager()->GetPlayerInfo().MaxHP)
		return;
	if (GameInst)
	{
		//나중에 수치별 예외처리
		GameInst->UpgradeHealth();
		Refresh();
	}
}
