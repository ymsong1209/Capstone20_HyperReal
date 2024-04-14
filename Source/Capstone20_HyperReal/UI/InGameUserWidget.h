// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "InGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API UInGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UCharacterHUDWidget* mCharacterHUD;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	UCharacterHUDWidget* GetCharacterHUD()	const
	{
		return mCharacterHUD;
	}
public:
	void SetHP(int32 HP, int32 HPMax);
	
};
