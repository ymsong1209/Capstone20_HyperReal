// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHUDWidget.h"

void UDamageHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UDamageHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mDamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
}

void UDamageHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDamageHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	FVector2D CurrentPosition;
	mAccLifeTime += InDeltaTime;
	if(IsValid(mOwner))
	{
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), mOwner->GetActorLocation() + FVector(0, 0, 0), CurrentPosition);
		mPrevLocation = CurrentPosition;
	}
	else
	{
		CurrentPosition = mPrevLocation;
	}
	CurrentPosition.Y -= 35.0f * mAccLifeTime;  // 초당 20픽셀 위로 이동
	SetRenderTranslation(CurrentPosition);

	// 알파값 감소
	float CurrentAlpha = RenderOpacity;
	CurrentAlpha -= 0.7f * InDeltaTime;  // 초당 0.5씩 투명해짐
	SetRenderOpacity(CurrentAlpha);

	// 알파값이 0이 되면 위젯 제거
	if (CurrentAlpha <= 0.0f)
	{
		RemoveFromParent();
	}
	
}

void UDamageHUDWidget::Init(int damage, AActor* Owner, bool isPlayer)
{
	if(!mDamageText)
	{
		UE_LOG(LogTemp, Error, TEXT("DamageText is nullptr"));
		return;
	}
	if(isPlayer)
	{
		mDamageText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));
		FSlateFontInfo FontInfo = mDamageText->Font;
		FontInfo.Size = 30;
		mDamageText->SetFont(FontInfo);
	}
	mDamageText->SetText(FText::FromString(FString::FromInt(damage)));
	mOwner = Owner;
	if (IsValid(Owner))
	{
		FVector2D ScreenPosition;
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), Owner->GetActorLocation() + FVector(0, 0, 0), ScreenPosition);
		SetRenderTranslation(ScreenPosition);
	}
}
