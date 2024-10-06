// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameModeBase.h"

#include "Character/SkeletonSoldierController.h"
#include "Character/SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGameUserWidget.h"
#include "CapStoneGameInstance.h"

AInGameModeBase::AInGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASkeletonSoldierController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/A_SJWContent/Character/BP_SkeletonSoldier.BP_SkeletonSoldier_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{

		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("Blueprint'/Game/A_SJWContent/Character/BP_SoldierController.BP_SoldierController_C'"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UInGameUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/UI_InGame.UI_InGame_C'"));
	if (WidgetClass.Succeeded())
	{
		mInGameWidgetClass = WidgetClass.Class;
	}
}

void AInGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AInGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;

	if (mInGameWidgetClass)
	{
		mInGameWidget = CreateWidget<UInGameUserWidget>(GetWorld(), mInGameWidgetClass);

		if (mInGameWidget)
			mInGameWidget->AddToViewport();
	}

	//FInputModeGameAndUI mode;
	//controller->SetInputMode(mode);
}

void AInGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AInGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}