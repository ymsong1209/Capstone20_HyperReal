// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWidget.h"
#include "Components/Button.h"
#include "UpgradeWidget.h"
#include "BodyStoreWidget.h"
#include "MagicWidget.h"
#include "Blueprint/UserWidget.h"
#include "BasecampWidget.generated.h"
/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBasecampWidget : public UMyWidget
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* mUpgradeButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* mMagicButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* mMaintainButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* mNextStageButton;

	UUpgradeWidget* UpgradeWidget;
	UMagicWidget* MagicWidget;
	UBodyStoreWidget* MaintainWidget;

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void UpgradeButtonClick();
	UFUNCTION()
	void MagicButtonClick();
	UFUNCTION()
	void MaintainButtonClick();
	UFUNCTION()
	void NextStageButtonClick();
	virtual void CloseUI() override;
	
};
