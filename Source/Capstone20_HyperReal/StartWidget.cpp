// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CapStoneGameInstance.h"
void UStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UStartWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mLoadButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadButton")));
	mEndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	mStartButton->OnClicked.AddDynamic(this,&UStartWidget::StartButtonClick);
	mLoadButton->OnClicked.AddDynamic(this, &UStartWidget::LoadButtonClick);
	mEndButton->OnClicked.AddDynamic(this, &UStartWidget::EndButtonClick);
}

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStartWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartWidget::StartButtonClick()
{
	UCapStoneGameInstance* pGameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

	if(pGameInst)
		pGameInst->DeleteSaveData();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BGBaseCampMap"));
}

void UStartWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UStartWidget::LoadButtonClick()
{
	{
		// ========================================
		// 플레이어 데이터 로드용 테스트 코드 - 서종원
		UCapStoneGameInstance* pGameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

		if (pGameInst)
		{
			pGameInst->LoadGameData();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Load Game Data Failed, no Game Instance"));
		}
		// =========================================
	}
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BGBaseCampMap"));
}

void UStartWidget::LoadBtnDisable()
{
	mLoadButton->SetIsEnabled(false);
}
