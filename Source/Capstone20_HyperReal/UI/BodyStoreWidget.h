// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "BodyStoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBodyStoreWidget : public UMyWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* HP_backButton;
	
	
	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* HP_MyMoneyText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* HPUpgradeButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProgressBar* RestoreprogressBar;
	
	
	int curCost;
	int MaxCost;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* UpgradeCostCurText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* UpgradeCostMaxText;
	
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	UFUNCTION()
	void CloseButtonUI();
	virtual void CloseUI() override;
	void Refresh();
	UFUNCTION()
	void Upgrade();
	
};
