﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../BaseLevelGameModeBase.h"
#include "BaseLevelWidget.h"
#include "Engine/Texture2D.h"
#include "Slate/SlateBrushAsset.h"
#include "Styling/SlateBrush.h"
#include "Math/UnrealMathUtility.h"
#include "../CapStoneGameInstance.h"
#include "../Manager/RuneManager.h"
#include "../Manager/PlayerManager.h"
#include "../GameData.h"
#include "../Item/Rune/Rune.h"

void UMagicWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMagicWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Magic_Button.Reserve(3);
	Magic_Name.Reserve(3);
	MagicDesc.Reserve(3);
	Magic_LevelText.Reserve(3);
	Magic_CostText.Reserve(3);
	arrRune.Reserve(3);
	for (int32 i = 1; i <= 3; i++)
	{
		FString WidgetName = FString::Printf(TEXT("MagicButton%d"), i);
		UButton* buttonWidget = Cast<UButton>(GetWidgetFromName(*WidgetName));
		if (buttonWidget)
		{
			Magic_Button.Add(buttonWidget);
		}
		WidgetName = FString::Printf(TEXT("MagicName%d"), i);
		UTextBlock* textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));
		textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));

		if (textWidget)
		{
			Magic_Name.Add(textWidget);
		}

		WidgetName = FString::Printf(TEXT("%dLevel"), i);
		UTextBlock* leveltextWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));
		textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));

		if (textWidget)
		{
			Magic_LevelText.Add(textWidget);
		}

		WidgetName = FString::Printf(TEXT("MagicDescription%d"), i);
		textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));
		if (textWidget)
		{
			MagicDesc.Add(textWidget);
		}

		WidgetName = FString::Printf(TEXT("Cost%d"), i);
		textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));
		if (textWidget)
		{
			Magic_CostText.Add(textWidget);
		}
	}
	Magic_backButton = Cast<UButton>(GetWidgetFromName(TEXT("MagicBackButton123")));
	//Magic_Button[0] = Cast<UButton>(GetWidgetFromName(TEXT("MagicButton1")));
	//Magic_Button[1] = Cast<UButton>(GetWidgetFromName(TEXT("MagicButton2")));
	//Magic_Button[2] = Cast<UButton>(GetWidgetFromName(TEXT("MagicButton3")));
	//
	//Magic_Name[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicName1")));
	//Magic_Name[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicName2")));
	//Magic_Name[2] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicName3")));
	//
	//MagicDesc[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicDescription1")));
	//MagicDesc[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicDescription2")));
	//MagicDesc[2] = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicDescription3")));

	Magic_backButton->OnClicked.AddDynamic(this, &UMagicWidget::CloseButtonUI);
	Magic_Button[0]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade0);
	Magic_Button[1]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade1);
	Magic_Button[2]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade2);

	Magic_MoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MoneyText")));
}

void UMagicWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//최초 이니셜라이즈 1번 진행해주기 
	//Refresh();
}

void UMagicWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMagicWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMagicWidget::CloseButtonUI()
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

void UMagicWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMagicWidget::Upgrade0()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		if (GameInst->GetRuneManager()->GetRuneCost(arrRune[0]->GetRuneType()) > gold)
			return;

		GameInst->UpgradeRune(arrRune[0]->GetRuneType());
		gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		int32 magicLevel;
		magicLevel = arrRune[0]->GetLevel();
		FString str = "Level " + FString::FromInt(magicLevel);
		Magic_LevelText[0]->SetText(FText::FromString(str));
		Magic_Button[0]->SetIsEnabled(false);
		FString gstr = FString::FromInt(gold);
		Magic_MoneyText->SetText(FText::FromString(gstr));
	}
}

void UMagicWidget::Upgrade1()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		if (GameInst->GetRuneManager()->GetRuneCost(arrRune[1]->GetRuneType()) > gold)
			return;

		GameInst->UpgradeRune(arrRune[1]->GetRuneType());
		gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		int32 magicLevel;
		magicLevel = arrRune[1]->GetLevel();
		FString str = "Level " + FString::FromInt(magicLevel);
		Magic_LevelText[1]->SetText(FText::FromString(str));
		Magic_Button[1]->SetIsEnabled(false);
		FString gstr = FString::FromInt(gold);
		Magic_MoneyText->SetText(FText::FromString(gstr));
	}
}

void UMagicWidget::Upgrade2()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		if (GameInst->GetRuneManager()->GetRuneCost(arrRune[2]->GetRuneType()) > gold)
			return;

		GameInst->UpgradeRune(arrRune[2]->GetRuneType());
		gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		int32 magicLevel;
		magicLevel = arrRune[2]->GetLevel();
		FString str = "Level " + FString::FromInt(magicLevel);
		Magic_LevelText[2]->SetText(FText::FromString(str));
		Magic_Button[2]->SetIsEnabled(false);
		FString gstr = FString::FromInt(gold);
		Magic_MoneyText->SetText(FText::FromString(gstr));
	}
}



void UMagicWidget::Refresh()
{
	UE_LOG(LogTemp, Log, TEXT("Rune Upgrade Widget refresh"));

	TArray<int32> Numbers;
	TArray<int32> Result;
	arrRune.Empty();
	// 1부터 10까지의 숫자를 배열에 추가
	for (int32 i = 0; i <= 9; ++i)
	{
		Numbers.Add(i);
	}
	
	// 랜덤하게 3개의 숫자를 뽑음
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Add(Numbers[Index]);
		Numbers.RemoveAt(Index);  // 중복 방지를 위해 선택한 숫자는 제거
	}
	
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
		FString gstr = FString::FromInt(gold);
		Magic_MoneyText->SetText(FText::FromString(gstr));
	}
	
	for (int32 i = 0; i < 3; i++)
	{
		
		//// 버튼 스타일 설정
		FButtonStyle ButtonStyle = Magic_Button[i]->WidgetStyle;
		URune* rune=GameInst->GetRuneManager()->GetRune((ERuneType)Result[i]);
		arrRune.Add(rune);
		ButtonStyle.Normal.SetResourceObject(rune->GetIconImage());
		ButtonStyle.Hovered.SetResourceObject(rune->GetIconImage());
		ButtonStyle.Pressed.SetResourceObject(rune->GetIconImage());
		
		Magic_Button[i]->SetStyle(ButtonStyle);
		FString name = rune->GetName();
		Magic_Name[i]->SetText(FText::FromString(name));
		FString desc = rune->GetExplan();
		MagicDesc[i]->SetText(FText::FromString(desc));

		int32 magicLevel = rune->GetLevel();
		FString str = "Level " + FString::FromInt(magicLevel);
		Magic_LevelText[i]->SetText(FText::FromString(str));

		int32 cost = GameInst->GetRuneManager()->GetRuneCost(rune->GetRuneType());
		str = FString::FromInt(cost);
		Magic_CostText[i]->SetText(FText::FromString(str));
	}
}
