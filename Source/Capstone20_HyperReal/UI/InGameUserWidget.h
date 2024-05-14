// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "CharacterHUDWidget.h"
#include "RewardWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "InGameUserWidget.generated.h"
class UImage;
class UTexture;
/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UInGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UCharacterHUDWidget* mCharacterHUD;
	URewardWidget* mRewardWidget;
	UTextBlock* mPrevGold;
	UTextBlock* mEarnGold;
	UTextBlock* mDestoryRate;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
private:
	class UImage* skillicon;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI Elements")
	TArray<UImage*> skillImages;
	TArray<UImage*> skillBackImages;
	class UMaterialInstanceDynamic* MatInst;
	float rate;
public:
	UCharacterHUDWidget* GetCharacterHUD()	const
	{
		return mCharacterHUD;
	}
public:
	void SetHP(int32 HP, int32 HPMax);
	void CalSkillCoolTime(int idx, float fRate);
	void SetSkillImage(int idx, UTexture* tex);
	void SetPrevGold(int gold);
	void SetEarnGold(int gold);
	void SetDestoryRate(float fRate);

	void OpenRewardUI(int gold,int building,int enemy);
};
