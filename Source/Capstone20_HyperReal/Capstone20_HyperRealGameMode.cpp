// Copyright Epic Games, Inc. All Rights Reserved.

#include "Capstone20_HyperRealGameMode.h"
#include "Capstone20_HyperRealPlayerController.h"
#include "Capstone20_HyperRealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACapstone20_HyperRealGameMode::ACapstone20_HyperRealGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACapstone20_HyperRealPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}