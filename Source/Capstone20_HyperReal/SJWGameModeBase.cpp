// Fill out your copyright notice in the Description page of Project Settings.


#include "SJWGameModeBase.h"

#include "Character/ClickMoveController.h"
#include "Character/SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"

ASJWGameModeBase::ASJWGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = AClickMoveController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/A_SJWContent/Character/BP_SkeletonSoldier"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/A_SJWContent/Character/BP_ClickMoveController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}


