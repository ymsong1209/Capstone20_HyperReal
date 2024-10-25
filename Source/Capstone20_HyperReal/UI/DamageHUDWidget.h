// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "DamageHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UDamageHUDWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* mDamageText;
	AActor* mOwner;
	FVector2D mPrevLocation;
	float mAccLifeTime;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void Init(int damage, AActor* Owner, bool isPlayer = false);
};
