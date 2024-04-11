// Fill out your copyright notice in the Description page of Project Settings.


#include "KHIGameModeBase.h"

AKHIGameModeBase::AKHIGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
	static ConstructorHelpers::FClassFinder<UStartWidget> startWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/UI_Start.UI_Start_C'"));
	if (startWidgetClass.Succeeded())
	{
		mStartWidgetClass = startWidgetClass.Class;
	}
}

void AKHIGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (mStartWidgetClass)
	{
		mStartWidget = CreateWidget<UStartWidget>(GetWorld(),mStartWidgetClass);
		if (mStartWidget)
			mStartWidget->AddToViewport();
	}
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;

	FInputModeUIOnly mode;
	controller->SetInputMode(mode);
}
