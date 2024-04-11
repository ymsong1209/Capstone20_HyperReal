// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
void UStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UStartWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mEndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	mStartButton->OnClicked.AddDynamic(this,&UStartWidget::StartButtonClick);
	mEndButton->OnClicked.AddDynamic(this, &UStartWidget::EndButtonClick);
}

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStartWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("KHIMap"));
}

void UStartWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
