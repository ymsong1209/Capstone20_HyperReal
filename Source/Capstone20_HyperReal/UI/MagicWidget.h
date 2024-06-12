// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWidget.h"
#include "Containers/Array.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MagicWidget.generated.h"

/**
 * 
 */
class URune;
UCLASS()
class CAPSTONE20_HYPERREAL_API UMagicWidget : public UMyWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* Magic_backButton;

	UPROPERTY()
	TArray<UButton*> Magic_Button;
	UPROPERTY()
	TArray<URune*> arrRune;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UButton* Magic_Button1;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UButton* Magic_Button2;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UButton* Magic_Button3;

	UPROPERTY()
	TArray<UTextBlock*> Magic_Name;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* Magic_Name1;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* Magic_Name2;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* Magic_Name3;


	UPROPERTY()
	TArray<UTextBlock*> MagicDesc;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* MagicDesc1;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* MagicDesc2;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UTextBlock* MagicDesc3;
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
	UFUNCTION()
	void Upgrade0();

	UFUNCTION()
	void Upgrade1();

	UFUNCTION()
	void Upgrade2();
	void Refresh();


	
};
