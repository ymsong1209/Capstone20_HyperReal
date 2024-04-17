// Fill out your copyright notice in the Description page of Project Settings.


#include "SJWGameModeBase.h"

#include "Character/SkeletonSoldierController.h"
#include "Character/SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"

ASJWGameModeBase::ASJWGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASkeletonSoldierController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/A_SJWContent/Character/BP_SkeletonSoldier.BP_SkeletonSoldier_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{

		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//// set default controller to our Blueprinted controller
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/A_SJWContent/Character/BP_ClickMoveController"));
	//if (PlayerControllerBPClass.Class != nullptr)
	//{
	//	PlayerControllerClass = PlayerControllerBPClass.Class;
	//}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("Blueprint'/Game/A_SJWContent/Character/BP_SoldierController.BP_SoldierController_C'"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}


