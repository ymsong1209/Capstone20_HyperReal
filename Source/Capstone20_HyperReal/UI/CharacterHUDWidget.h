// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UCharacterHUDWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UProgressBar* mHPBar;
	UProgressBar* mSPBar;
	UTextBlock* mHPText;
	UTextBlock* mMPText;
	
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void SetHPPercent(float Percent)
	{
		if (Percent < 0.f)
			Percent = 0.f;

		else if (Percent > 1.f)
			Percent = 1.f;

		mHPBar->SetPercent(Percent);
	}
	void SetHPText(int HP, int HPMax)
	{
		mHPText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), HP, HPMax)));
	}
	void SetSPPercent(float Percent)
	{
		if (Percent < 0.f)
			Percent = 0.f;

		else if (Percent > 1.f)
			Percent = 1.f;

		mSPBar->SetPercent(Percent);
	}
	void SetSPText(int SP, int SPMax)
	{
		mMPText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), SP, SPMax)));
	}
};
