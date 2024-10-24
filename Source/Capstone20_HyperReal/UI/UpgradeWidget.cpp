// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeWidget.h"
#include "../InGameModeBase.h"
#include "../BaseLevelGameModeBase.h"
#include "BaseLevelWidget.h"
#include "../UI/InGameUserWidget.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "../Manager/PlayerManager.h"
#include "../GameData.h"
#include "TimerManager.h"
void UUpgradeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUpgradeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	state = EPlayerUpgradeType::None;
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
	PhaseText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Phase")));;
	ProGA = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProgressA")));;
	ProGB = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProgressB")));;
	EffText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EffectText")));;

	frame1 = Cast<UImage>(GetWidgetFromName(TEXT("frame11")));;
	frame2 = Cast<UImage>(GetWidgetFromName(TEXT("frame22")));;
	frame3 = Cast<UImage>(GetWidgetFromName(TEXT("frame33")));;

	fadeDuration = 1.f;

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
	if (bIsFading)
	{
		FLinearColor Color = EffText->ColorAndOpacity.GetSpecifiedColor();

		// 투명도를 줄임
		Color.A -= InDeltaTime / fadeDuration;
		EffText->SetColorAndOpacity(Color);

		// 투명도가 0 이하가 되면 텍스트를 숨김
		if (Color.A <= 0.0f)
		{
			EffText->SetVisibility(ESlateVisibility::Collapsed);
			bIsFading = false;
		}
	}
	
}

void UUpgradeWidget::AttackIconButtonClick()
{
	if (!secondphase)
	{
		secondphase = true;
		StartSecondPhase();
	}
	
	
	state = EPlayerUpgradeType::Attack;
	FString imageName = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/A_SYMContent/UI/image/AttackIcon.AttackIcon'"));
	UTexture2D* NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *imageName));
	if (NewTexture)
	{
		targetIconImage->SetBrushFromTexture(NewTexture);
	}
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (PlayerCharacter)
	{
		
		if (GameInst)
		{
			//int gold=PlayerCharacter->GetPlayerInfo().LevelAccGold+ PlayerCharacter->GetPlayerInfo().TotalGold;
			
		}
	}
	int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
	UE_LOG(LogTemp, Log, TEXT("curgold : %d"), GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold);
	FString gstr = FString::FromInt(gold);
	MyMoneyText->SetText(FText::FromString(gstr));
	InfoText->SetText(FText::FromString(TEXT("공격력 강화")));
	//프로그레스 바 및 강화비용 설정
	int curLevel = GameInst->GetPlayerManager()->GetPlayerInfo().AttackLevel;
	UpgradeText eut = (UpgradeText)curLevel;
	FString EnumString = EnumToString(eut)+TEXT("단계");
	PhaseText->SetText(FText::FromString(EnumString));
	//임시코드
	int cost = GameInst->GetPlayerManager()->GetUpgradeCost(EPlayerUpgradeType::Attack);
	FString str = FString::FromInt(cost);
	UpgradeCostText->SetText(FText::FromString(str));
	float rate = (GameInst->GetPlayerManager()->GetPlayerInfo().AttackProgress)/100.f;
	progressBar->SetPercent(rate);
	
	int iRate = (GameInst->GetPlayerManager()->GetPlayerInfo().AttackProgress);
	str = FString::FromInt(iRate);
	ProGA->SetText(FText::FromString(str));

}

void UUpgradeWidget::HPIconButtonClick()
{
	if (!secondphase)
	{
		secondphase = true;
		StartSecondPhase();
	}
	state = EPlayerUpgradeType::Health;
	FString imageName = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/A_SYMContent/UI/image/HealthIcon.HealthIcon'"));
	UTexture2D* NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *imageName));
	if (NewTexture)
	{
		targetIconImage->SetBrushFromTexture(NewTexture);
	}
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (PlayerCharacter)
	{
		
		if (GameInst)
		{
			//int gold = PlayerCharacter->GetPlayerInfo().LevelAccGold + PlayerCharacter->GetPlayerInfo().TotalGold;
			//FString str = FString::FromInt(gold);
			//MyMoneyText->SetText(FText::FromString(str));
		}
	}
	int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
	UE_LOG(LogTemp, Log, TEXT("curgold : %d"), GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold);
	FString gstr = FString::FromInt(gold);
	MyMoneyText->SetText(FText::FromString(gstr));
	InfoText->SetText(FText::FromString(TEXT("체력 촉진")));
	int curLevel = GameInst->GetPlayerManager()->GetPlayerInfo().HealthLevel;
	UpgradeText eut = (UpgradeText)curLevel;
	FString EnumString = EnumToString(eut) + TEXT("단계");
	PhaseText->SetText(FText::FromString(EnumString));
	//프로그레스 바 및 강화비용 설정
	int cost = GameInst->GetPlayerManager()->GetUpgradeCost(EPlayerUpgradeType::Health);;
	FString str = FString::FromInt(cost);
	UpgradeCostText->SetText(FText::FromString(str));
	float rate = (GameInst->GetPlayerManager()->GetPlayerInfo().HealthProgress) / 100.f;
	progressBar->SetPercent(rate);

	int iRate = (GameInst->GetPlayerManager()->GetPlayerInfo().HealthProgress);
	str = FString::FromInt(iRate);
	ProGA->SetText(FText::FromString(str));

}

void UUpgradeWidget::SoulIconButtonClick()
{
	if (!secondphase)
	{
		secondphase = true;
		StartSecondPhase();
	}
	state = EPlayerUpgradeType::Soul;
	FString imageName = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/A_SYMContent/UI/image/SoulIcon.SoulIcon'"));
	UTexture2D* NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *imageName));
	if (NewTexture)
	{
		targetIconImage->SetBrushFromTexture(NewTexture);
	}
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (PlayerCharacter)
	{
		
		if (GameInst)
		{
			//int gold = PlayerCharacter->GetPlayerInfo().LevelAccGold + PlayerCharacter->GetPlayerInfo().TotalGold;
			//FString str = FString::FromInt(gold);
			//MyMoneyText->SetText(FText::FromString(str));
		}
	}
	InfoText->SetText(FText::FromString(TEXT("영혼력 증대")));
	//프로그레스 바 및 강화비용 설정
	int gold = GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold;
	UE_LOG(LogTemp, Log, TEXT("curgold : %d"), GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold);
	FString gstr = FString::FromInt(gold);
	MyMoneyText->SetText(FText::FromString(gstr));
	int curLevel = GameInst->GetPlayerManager()->GetPlayerInfo().SoulLevel;
	UpgradeText eut = (UpgradeText)curLevel;
	FString EnumString = EnumToString(eut) + TEXT("단계");
	PhaseText->SetText(FText::FromString(EnumString));

	int cost = GameInst->GetPlayerManager()->GetUpgradeCost(EPlayerUpgradeType::Soul);
	FString str = FString::FromInt(cost);
	UpgradeCostText->SetText(FText::FromString(str));
	float rate = (GameInst->GetPlayerManager()->GetPlayerInfo().SoulProgress) / 100.f;
	progressBar->SetPercent(rate);

	int iRate = (GameInst->GetPlayerManager()->GetPlayerInfo().SoulProgress);
	str = FString::FromInt(iRate);
	ProGA->SetText(FText::FromString(str));

}

void UUpgradeWidget::CloseButtonUI()
{
	if (secondphase)
	{
		RestoreFisrtPhase();
		secondphase = false;
		state = EPlayerUpgradeType::None;
	}
	else
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
	frame1->SetVisibility(ESlateVisibility::Visible);
	frame2->SetVisibility(ESlateVisibility::Visible);
	frame3->SetVisibility(ESlateVisibility::Visible);
	PhaseText->SetVisibility(ESlateVisibility::Collapsed);
	ProGB->SetVisibility(ESlateVisibility::Collapsed);
	ProGA->SetVisibility(ESlateVisibility::Collapsed);
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
	PhaseText->SetVisibility(ESlateVisibility::Visible);
	ProGB->SetVisibility(ESlateVisibility::Visible);
	ProGA->SetVisibility(ESlateVisibility::Visible);

	AttackIconButton->SetVisibility(ESlateVisibility::Collapsed);
	HPIconButton->SetVisibility(ESlateVisibility::Collapsed);
	SoulIconButton->SetVisibility(ESlateVisibility::Collapsed);
	frame1->SetVisibility(ESlateVisibility::Collapsed);
	frame2->SetVisibility(ESlateVisibility::Collapsed);
	frame3->SetVisibility(ESlateVisibility::Collapsed);
}

void UUpgradeWidget::Upgrade()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		//나중에 수치별 예외처리
		//UE_LOG(LogTemp, Log, TEXT("goldbefore : %d"), GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold);
		//UE_LOG(LogTemp, Log, TEXT("goldafter : %d"), GameInst->GetPlayerManager()->GetPlayerInfo().TotalGold);
		int curStateLevel=CheckStateLevel(state);
		if (curStateLevel == 5|| GameInst->GetPlayerManager()->IsUpgradeAvail(state))
			return;
		GameInst->UpgradePlayerStat(state);
		switch (state)
		{
		case EPlayerUpgradeType::None:
			break;
		case EPlayerUpgradeType::Attack:
			AttackIconButtonClick();
			break;
		case EPlayerUpgradeType::Health:
			HPIconButtonClick();
			break;
		case EPlayerUpgradeType::Soul:
			SoulIconButtonClick();
			break;
		case EPlayerUpgradeType::End:
			break;
		default:
			break;
		}
	}
}

int32 UUpgradeWidget::CheckStateLevel(EPlayerUpgradeType type)
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	int curLevel = 0;
	if (type == EPlayerUpgradeType::Attack)
	{
		curLevel= GameInst->GetPlayerManager()->GetPlayerInfo().AttackLevel;
	}
	else if(type == EPlayerUpgradeType::Health)
	{
		curLevel = GameInst->GetPlayerManager()->GetPlayerInfo().HealthLevel;
	}
	else if (type == EPlayerUpgradeType::Soul)
	{
		curLevel = GameInst->GetPlayerManager()->GetPlayerInfo().SoulLevel;
	}
	return curLevel;
}

void UUpgradeWidget::StartComboTextEffect(int value)
{

	EffText->SetVisibility(ESlateVisibility::Visible);

	FString str = "+"+FString::FromInt(value);
	EffText->SetText(FText::FromString(str));

	FLinearColor Color = EffText->ColorAndOpacity.GetSpecifiedColor();
	Color.A = 1.0f;
	EffText->SetColorAndOpacity(Color);

	bIsFading = true;

}
