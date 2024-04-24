// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture.h"
void UInGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInGameUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCharacterHUD = Cast<UCharacterHUDWidget>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	skillicon = Cast<UImage>(GetWidgetFromName(TEXT("skillicon1")));

	const int32 NumImages = 4;
	skillImages.Reserve(NumImages);  // ���� ����ȭ�� ���� �迭 ũ�� �̸� ����
	skillBackImages.Reserve(NumImages);

	for (int32 i = 1; i <= NumImages; i++)
	{
		// ���� �̸� ����: skillicon1, skillicon2, ..., skillicon5
		FString WidgetName = FString::Printf(TEXT("skillicon%d"), i);

		// ���� �̸����� UImage ã��
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
