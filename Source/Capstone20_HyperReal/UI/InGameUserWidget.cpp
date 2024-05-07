// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture.h"
#include "../GameData.h"
void UInGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInGameUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCharacterHUD = Cast<UCharacterHUDWidget>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	mPrevGold = Cast<UTextBlock>(GetWidgetFromName(TEXT("PrevMoney")));
	mEarnGold = Cast<UTextBlock>(GetWidgetFromName(TEXT("earnMoney")));
	mDestoryRate = Cast<UTextBlock>(GetWidgetFromName(TEXT("DestroyRate")));

	
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
}

void UInGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetPrevGold(1000);
	SetEarnGold(500);
	SetDestoryRate(25.7f);
	
}

void UInGameUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (skillicon && skillicon->GetDynamicMaterial()) {
		//UE_LOG(LogTemp, Display, TEXT("dynamiccalled"));
		rate += InDeltaTime * 0.6f;
		if (rate >= 1.f)
			rate = 0;
		skillImages[0]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
		skillImages[1]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
		skillImages[2]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
		skillImages[3]->GetDynamicMaterial()->SetScalarParameterValue(FName("Percent"), rate);
		UTexture* NewTexture = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon1.icon1'")));
		skillImages[0]->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillImage"), NewTexture);
		NewTexture = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon2.icon2'")));
		skillImages[1]->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillImage"), NewTexture);
		NewTexture = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon3.icon3'")));
		skillImages[2]->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillImage"), NewTexture);
		NewTexture = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon4.icon4'")));
		skillImages[3]->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillImage"), NewTexture);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("skillicon does not have a dynamic material"));
	}
}
void UInGameUserWidget::SetHP(int32 HP, int32 HPMax)
{
	mCharacterHUD->SetHPPercent(HP / (float)HPMax);
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

void UInGameUserWidget::SetDestoryRate(float fRate)
{
	int iRate=FMath::FloorToInt(fRate);
	FString str=FString::FromInt(iRate) + "%";
	mDestoryRate->SetText(FText::FromString(str));
}


