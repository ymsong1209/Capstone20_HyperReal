// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWidget.h"
#include "../GameData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWidget.generated.h"

UENUM(BlueprintType)
enum class UpgradeText : uint8
{
	NONE,
	I,
	II,
	III,
	IV,
	V,
	VI,
	VII,
	VIII,
	IX,
	X,
};
/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UUpgradeWidget : public UMyWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* backButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* AttackIconButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* HPIconButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* SoulIconButton;

	bool secondphase;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* targetIconImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* InfoText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* MoneyIconImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* MyMoneyText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* UpgradeButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProgressBar* progressBar;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* progressBarBorder;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* UpgradeCostText;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* PhaseText;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* ProGA;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* ProGB;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* EffText;
	/// <summary>
	/// //////////////////
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* frame1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* frame2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* frame3;

	EPlayerUpgradeType state;
	float fadeDuration;
	bool bIsFading;

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	
	UFUNCTION()
	void AttackIconButtonClick();
	UFUNCTION()
	void HPIconButtonClick();
	UFUNCTION()
	void SoulIconButtonClick();
	UFUNCTION()
	void CloseButtonUI() ;
	virtual void CloseUI() override;
	void RestoreFisrtPhase();
	void StartSecondPhase();
	UFUNCTION()
	void Upgrade();
	int32 CheckStateLevel(EPlayerUpgradeType type);

	UFUNCTION()
	void StartComboTextEffect(int value);
	
};
