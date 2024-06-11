// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Containers/Array.h"
#include "MyWidget.h"
#include "CharacterHUDWidget.h"
#include "RewardWidget.h"
#include "BasecampWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "BaseLevelWidget.generated.h"


class UImage;
class UTexture;
/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UBaseLevelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	TArray<UMyWidget*> ActivateWidgets;
protected:
	UBasecampWidget* mBasecampWidget;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:
	void PushWidget(UMyWidget* Widget);
	UMyWidget* PopWidget();
	UMyWidget* TopWidget();
	void CloseUI();

};
