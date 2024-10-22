// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"
void UInGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInGameUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCharacterHUD = Cast<UCharacterHUDWidget>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	mRewardWidget = Cast<URewardWidget>(GetWidgetFromName(TEXT("RewardWidget")));
	mBasecampWidget = Cast<UBasecampWidget>(GetWidgetFromName(TEXT("BaseCampWidget")));
	mPrevGold = Cast<UTextBlock>(GetWidgetFromName(TEXT("PrevMoney")));
	mEarnGold = Cast<UTextBlock>(GetWidgetFromName(TEXT("earnMoney")));
	mDestoryRate = Cast<UTextBlock>(GetWidgetFromName(TEXT("DestroyRate")));
	mYouWin = Cast<UTextBlock>(GetWidgetFromName(TEXT("YouWin")));
	mYouDied = Cast<UTextBlock>(GetWidgetFromName(TEXT("YouDied")));
	mCheck = Cast<UButton>(GetWidgetFromName(TEXT("CheckButton")));
	
	FString	t = "Testcode";
	mPrevGold->SetText(FText::FromString(t));
	mEarnGold->SetText(FText::FromString(t));

	skillicon = Cast<UImage>(GetWidgetFromName(TEXT("skillicon1")));

	const int32 NumImages = 4;
	skillImages.Reserve(NumImages);  // 성능 최적화를 위해 배열 크기 미리 설정
	skillBackImages.Reserve(NumImages);

	for (int32 i = 1; i <= NumImages; i++)
	{
		// 위젯 이름 생성: skillicon1, skillicon2, ..., skillicon5
		FString WidgetName = FString::Printf(TEXT("skillicon%d"), i);

		// 위젯 이름으로 UImage 찾기
		UImage* ImageWidget = Cast<UImage>(GetWidgetFromName(*WidgetName));
		if (ImageWidget)
		{
			skillImages.Add(ImageWidget);
		}
	}
	for (int32 i = 1; i <= NumImages; i++)
	{
		FString wName = FString::Printf(TEXT("skillBack%d"), i);
		UImage* ImageWidget = Cast<UImage>(GetWidgetFromName(*wName));
		if (ImageWidget)
		{
			skillBackImages.Add(ImageWidget);
		}
		FString imageName = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon%d.icon%d'"), i,i);
		//const TCHAR* tcimageName = *imageName;
		UTexture2D* NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *imageName));
		if (NewTexture)
		{
			skillBackImages[i-1]->SetBrushFromTexture(NewTexture);
		}
	}
	mCheck->OnClicked.AddDynamic(this, &UInGameUserWidget::Restart);
}

void UInGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//TODO : datatable에서 세팅해와야함.
	SetPrevGold(0);
	SetEarnGold(0);
	mRewardWidget->setDestroyBuildingCount(10);
	mRewardWidget->setRewardMoney(400);
	mRewardWidget->SetVisibility(ESlateVisibility::Collapsed);
	mBasecampWidget->SetVisibility(ESlateVisibility::Collapsed);
	mYouWin->SetVisibility(ESlateVisibility::Collapsed);
	mYouDied->SetVisibility(ESlateVisibility::Collapsed);
	mCheck->SetVisibility(ESlateVisibility::Collapsed);
}

void UInGameUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// if (skillicon && skillicon->GetDynamicMaterial()) {
	// 	//UE_LOG(LogTemp, Display, TEXT("dynamiccalled"));
	// 	rate += InDeltaTime * 0.6f;
	// 	if (rate >= 1.f)
	// 		rate = 0;
	// 	skillImages[0]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
	// 	skillImages[1]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
	// 	skillImages[2]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
	// 	skillImages[3]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
	// }
	// else {
	// 	//UE_LOG(LogTemp, Warning, TEXT("skillicon does not have a dynamic material"));
	// }
}
void UInGameUserWidget::SetHP(int32 HP, int32 HPMax)
{
	mCharacterHUD->SetHPPercent(HP / (float)HPMax);
}
void UInGameUserWidget::SetSP(int32 SP, int32 SPMax)
{
	mCharacterHUD->SetSPPercent(SP / (float)SPMax);
}
void UInGameUserWidget::CalSkillCoolTime(int idx, float fRate)
{
	if (skillImages[idx] && skillImages[idx]->GetDynamicMaterial())
	{
		skillImages[idx]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), fRate);
	}
}

void UInGameUserWidget::SetSkillImage(int idx, UTexture* tex)
{
	if (skillImages[idx] && skillImages[idx]->GetDynamicMaterial())
	{
		skillImages[idx]->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillImage"), tex);
	}
}

void UInGameUserWidget::SetSkillBackImage(int idx, UTexture2D* tex)
{
	if (skillImages[idx])
	{
		skillBackImages[idx]->SetBrushFromTexture(tex);
	}
}

void UInGameUserWidget::SetPrevGold(int gold)
{
	mPrevGold->SetText(FText::FromString(FString::FromInt(gold)));
}

void UInGameUserWidget::SetEarnGold(int gold)
{
	FString str = "+";
	str += FString::FromInt(gold);
	mEarnGold->SetText(FText::FromString(str));
}

void UInGameUserWidget::SetDestroyRate(float fRate)
{
	int iRate=FMath::FloorToInt(fRate);
	FString str=FString::FromInt(iRate) + "%";
	mDestoryRate->SetText(FText::FromString(str));
}

void UInGameUserWidget::OpenRewardUI(int gold, int building, int enemy)
{
	mRewardWidget->SetVisibility(ESlateVisibility::Visible);
	mRewardWidget->setRewardMoney(gold);
	mRewardWidget->setDestroyBuildingCount(building);
	mRewardWidget->setKillEnemyCount(enemy);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter)return;
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if(!GameInst)return;
	GameInst->UpdatePlayerGold();
}

void UInGameUserWidget::CloseRewardUI()
{
	mRewardWidget->SetVisibility(ESlateVisibility::Collapsed);
	mRewardWidget->setRewardMoney(0);
	mRewardWidget->setDestroyBuildingCount(0);
	mRewardWidget->setKillEnemyCount(0);
	//basecamp 위젯 활성화하기
	//mBasecampWidget->SetVisibility(ESlateVisibility::Visible);
	//PushWidget(mBasecampWidget);
}

void UInGameUserWidget::CloseUI()
{
	if (ActivateWidgets.Num()==0)
	{
		CloseRewardUI();
	}
	else
	{
		UMyWidget* widget = TopWidget();
		PopWidget();
		widget->CloseUI();
	}
	
	
}

void UInGameUserWidget::TestOpenTrigger()
{
	if(mBasecampWidget->IsVisible())
		mBasecampWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		mBasecampWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInGameUserWidget::PushWidget(UMyWidget* widget)
{
	if (widget)
	{
		ActivateWidgets.Add(widget);
	}
}

UMyWidget* UInGameUserWidget::PopWidget()
{
	if (ActivateWidgets.Num() == 0)
	{
		return nullptr;
	}

	UMyWidget* TopWidget = ActivateWidgets.Last();
	ActivateWidgets.RemoveAt(ActivateWidgets.Num() - 1);

	return TopWidget;
}

UMyWidget* UInGameUserWidget::TopWidget()
{
	if (ActivateWidgets.Num() == 0)
	{
		return nullptr;
	}

	return ActivateWidgets.Last();
}

void UInGameUserWidget::YouWin()
{
	mYouWin->SetVisibility(ESlateVisibility::Visible);
	mCheck->SetVisibility(ESlateVisibility::Visible);
}

void UInGameUserWidget::YouDied()
{
	mYouDied->SetVisibility(ESlateVisibility::Visible);
	mCheck->SetVisibility(ESlateVisibility::Visible);
}

void UInGameUserWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("KHIStartMap"));
}






