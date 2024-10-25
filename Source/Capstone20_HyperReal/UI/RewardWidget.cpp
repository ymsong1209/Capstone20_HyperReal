// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardWidget.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"

void URewardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URewardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	RewardMoney = Cast<UTextBlock>(GetWidgetFromName(TEXT("RewardMoneyText")));
	KillEnemyCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillEnemyCountText")));
	m_RecallButton = Cast<UButton>(GetWidgetFromName(TEXT("RecallButton")));

	m_RecallButton->OnClicked.AddDynamic(this, &URewardWidget::ReturnToBaseCampLevel);
}

void URewardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URewardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void URewardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void URewardWidget::setRewardMoney(int gold)
{
	FString str = "+";
	str += FString::FromInt(gold);
	RewardMoney->SetText(FText::FromString(str));
}


void URewardWidget::setKillEnemyCount(int count)
{
	KillEnemyCount->SetText(FText::FromString(FString::FromInt(count)));
}

void URewardWidget::ReturnToBaseCampLevel()
{
	UCapStoneGameInstance* gameInst = Cast<UCapStoneGameInstance>(GetGameInstance());
	if (gameInst)
		gameInst->SaveGameData();

	APlayerCharacter* pChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (pChar)
		pChar->EscapeFunction();
}

