// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeWidget.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"
void UUpgradeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUpgradeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	state = UpgradeState::None;
	backButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton123")));
	AttackIconButton = Cast<UButton>(GetWidgetFromName(TEXT("AttackIcon")));
	HPIconButton = Cast<UButton>(GetWidgetFromName(TEXT("HPIcon")));
	SoulIconButton = Cast<UButton>(GetWidgetFromName(TEXT("SoulIcon")));

	targetIconImage = Cast<UImage>(GetWidgetFromName(TEXT("TargetIcon")));;
	InfoText= Cast<UTextBlock>(GetWidgetFromName(TEXT("InfoText")));;
	MoneyIconImage = Cast<UImage>(GetWidgetFromName(TEXT("MoneyIcon")));;
	MyMoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyMoney")));;
	UpgradeButton = Cast<UButton>(GetWidgetFromName(TEXT("PlusButton")));;
	progressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progress")));;
	progressBarBorder = Cast<UImage>(GetWidgetFromName(TEXT("ProgressBorder")));;
	UpgradeCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeCost")));;

	frame1 = Cast<UImage>(GetWidgetFromName(TEXT("frame11")));;
	frame2 = Cast<UImage>(GetWidgetFromName(TEXT("frame22")));;
	frame3 = Cast<UImage>(GetWidgetFromName(TEXT("frame33")));;


	backButton->OnClicked.AddDynamic(this, &UUpgradeWidget::CloseButtonUI);
	AttackIconButton->OnClicked.AddDynamic(this, &UUpgradeWidget::AttackIconButtonClick);
	HPIconButton->OnClicked.AddDynamic(this, &UUpgradeWidget::HPIconButtonClick);
	SoulIconButton->OnClicked.AddDynamic(this, &UUpgradeWidget::SoulIconButtonClick);
	UpgradeButton->OnClicked.AddDynamic(this, &UUpgradeWidget::Upgrade);
}

void UUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RestoreFisrtPhase();
}

void UUpgradeWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUpgradeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);
}

void UUpgradeWidget::AttackIconButtonClick()
{
	secondphase = true;
	StartSecondPhase();
	
	state = UpgradeState::Attack;
	FString imageName = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Basecamp/UpgradeUI/AttackIcon.AttackIcon'"));
	UTexture2D* NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *imageName));
	if (NewTexture)
	{
		targetIconImage->SetBrushFromTexture(NewTexture);
	}
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
		if (GameInst)
		{
			int gold=PlayerCharacter->GetInfo().LevelAccGold+ PlayerCharacter->GetInfo().TotalGold;
			FString str = FString::FromInt(gold);
			MyMoneyText->SetText(FText::FromString(str));
		}
	}
	FString	t = "Testcode";
	InfoText->SetText(FText::FromString(t));
	//���α׷��� �� �� ��ȭ��� ����

	
}

void UUpgradeWidget::HPIconButtonClick()
{
	secondphase = true;
	StartSecondPhase();
}

void UUpgradeWidget::SoulIconButtonClick()
{
	secondphase = true;
	StartSecondPhase();
}

void UUpgradeWidget::CloseButtonUI()
{
	if (secondphase)
	{
		RestoreFisrtPhase();
		secondphase = false;
	}
	else
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
}

void UUpgradeWidget::CloseUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UUpgradeWidget::RestoreFisrtPhase()
{
	targetIconImage->SetVisibility(ESlateVisibility::Collapsed);
	InfoText->SetVisibility(ESlateVisibility::Collapsed);
	MoneyIconImage->SetVisibility(ESlateVisibility::Collapsed);
	MyMoneyText->SetVisibility(ESlateVisibility::Collapsed);
	UpgradeButton->SetVisibility(ESlateVisibility::Collapsed);
	progressBar->SetVisibility(ESlateVisibility::Collapsed);
	progressBarBorder->SetVisibility(ESlateVisibility::Collapsed);
	UpgradeCostText->SetVisibility(ESlateVisibility::Collapsed);

	AttackIconButton->SetVisibility(ESlateVisibility::Visible);
	HPIconButton->SetVisibility(ESlateVisibility::Visible);
	SoulIconButton->SetVisibility(ESlateVisibility::Visible);
	frame1->SetVisibility(ESlateVisibility::Collapsed);
	frame2->SetVisibility(ESlateVisibility::Collapsed);
	frame3->SetVisibility(ESlateVisibility::Collapsed);
}

void UUpgradeWidget::StartSecondPhase()
{
	targetIconImage->SetVisibility(ESlateVisibility::Visible);
	InfoText->SetVisibility(ESlateVisibility::Visible);
	MoneyIconImage->SetVisibility(ESlateVisibility::Visible);
	MyMoneyText->SetVisibility(ESlateVisibility::Visible);
	UpgradeButton->SetVisibility(ESlateVisibility::Visible);
	progressBar->SetVisibility(ESlateVisibility::Visible);
	progressBarBorder->SetVisibility(ESlateVisibility::Visible);
	UpgradeCostText->SetVisibility(ESlateVisibility::Visible);

	AttackIconButton->SetVisibility(ESlateVisibility::Collapsed);
	HPIconButton->SetVisibility(ESlateVisibility::Collapsed);
	SoulIconButton->SetVisibility(ESlateVisibility::Collapsed);
	frame1->SetVisibility(ESlateVisibility::Collapsed);
	frame2->SetVisibility(ESlateVisibility::Collapsed);
	frame3->SetVisibility(ESlateVisibility::Collapsed);
}

void UUpgradeWidget::Upgrade()
{
}
