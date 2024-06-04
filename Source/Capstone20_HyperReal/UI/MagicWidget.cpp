// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "Engine/Texture2D.h"
#include "Slate/SlateBrushAsset.h"
#include "Styling/SlateBrush.h"
#include "Math/UnrealMathUtility.h"
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
		if (textWidget)
		{
			Magic_Name.Add(textWidget);
		}
		WidgetName = FString::Printf(TEXT("MagicDescription%d"), i);
		textWidget = Cast<UTextBlock>(GetWidgetFromName(*WidgetName));
		if (textWidget)
		{
			MagicDesc.Add(textWidget);
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
	Magic_Button[0]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade);
	Magic_Button[1]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade);
	Magic_Button[2]->OnClicked.AddDynamic(this, &UMagicWidget::Upgrade);
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

void UMagicWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMagicWidget::Upgrade()
{
}

void UMagicWidget::Refresh()
{
	//TArray<int32> Numbers;
	//TArray<int32> Result;
	//
	//// 1부터 10까지의 숫자를 배열에 추가
	//for (int32 i = 1; i <= 10; ++i)
	//{
	//	Numbers.Add(i);
	//}
	//
	//// 랜덤하게 3개의 숫자를 뽑음
	//for (int32 i = 0; i < 3; ++i)
	//{
	//	int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
	//	Result.Add(Numbers[Index]);
	//	Numbers.RemoveAt(Index);  // 중복 방지를 위해 선택한 숫자는 제거
	//}
	//
	//
	//for (int32 i = 0; i < 3; i++)
	//{
	//	
	//	//// 버튼 스타일 설정
	//	FButtonStyle ButtonStyle = Magic_Button[i]->WidgetStyle;
	//	//ButtonStyle.Normal.SetResourceObject(NewTexture);
	//	//ButtonStyle.Hovered.SetResourceObject(NewTexture);
	//	//ButtonStyle.Pressed.SetResourceObject(NewTexture);
	//	
	//	Magic_Button[i]->SetStyle(ButtonStyle);
	//	//Magic_Name[i]->SetText();
	//	//MagicDesc[i]->SetText();
	//}
}

