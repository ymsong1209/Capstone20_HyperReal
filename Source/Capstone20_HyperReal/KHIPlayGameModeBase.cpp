// Fill out your copyright notice in the Description page of Project Settings.


#include "KHIPlayGameModeBase.h"
#include "Capstone20_HyperRealPlayerController.h"
#include "Capstone20_HyperRealCharacter.h"
#include "UObject/ConstructorHelpers.h"
AKHIPlayGameModeBase::AKHIPlayGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACapstone20_HyperRealPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/A_SJWContent/Character/BP_SkeletonSoldier"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UInGameUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/UI_InGame.UI_InGame_C'"));
	if (WidgetClass.Succeeded())
	{
		mInGameWidgetClass = WidgetClass.Class;
	}
}

void AKHIPlayGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AKHIPlayGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;

	if (mInGameWidgetClass)
	{
		mInGameWidget = CreateWidget<UInGameUserWidget>(GetWorld(), mInGameWidgetClass);

		if (mInGameWidget)
			mInGameWidget->AddToViewport();

		// RemoveFromViewport : 뷰포트에서 제거
	}

	FInputModeGameAndUI mode;
	controller->SetInputMode(mode);
}

void AKHIPlayGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AKHIPlayGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
