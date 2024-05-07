// Fill out your copyright notice in the Description page of Project Settings.


#include "KHIGameInstance.h"

UKHIGameInstance::UKHIGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>	PlayerTableAsset(TEXT("/Script/Engine.DataTable'/Game/A_KHIContent/DataTable/PlayerDT.PlayerDT'"));

	if (PlayerTableAsset.Succeeded())
		mPlayerInfoTable = PlayerTableAsset.Object;
}
