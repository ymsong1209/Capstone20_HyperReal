// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelGameModeBase.h"
#include "Character/SkeletonSoldierController.h"
#include "Character/SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/BaseLevelWidget.h"
ABaseLevelGameModeBase::ABaseLevelGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UBaseLevelWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/UI_BaseLevel.UI_BaseLevel_C'"));
	if (WidgetClass.Succeeded())
	{
		mBaseLevelWidgetClass = WidgetClass.Class;
	}
}
void ABaseLevelGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABaseLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;

	if (mBaseLevelWidgetClass)
	{
		mBaseLevelWidget = CreateWidget<UBaseLevelWidget>(GetWorld(), mBaseLevelWidgetClass);

		if (mBaseLevelWidget)
			mBaseLevelWidget->AddToViewport();
	}

	//FInputModeGameAndUI mode;
	//controller->SetInputMode(mode);
}

void ABaseLevelGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseLevelGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

