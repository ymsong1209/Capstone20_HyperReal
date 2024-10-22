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

#include "CapStoneGameInstance.h"
#include "Manager/PlayerManager.h"
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

	{
		// ========================================
		// 플레이어 데이터 로드용 테스트 코드 - 서종원
		UCapStoneGameInstance* pGameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

		if (pGameInst)
		{
			if (pGameInst->IsSaveDataExist())
			{
				// 저장 데이터 존재 - load game 버튼 활성화
				UE_LOG(LogTemp, Warning, TEXT("Save Data exist"));
			}
			else
			{
				// 저장 데이터 없음 - load game 버튼 비활성화 
				UE_LOG(LogTemp, Warning, TEXT("No Save Data"));
				mStartWidget->LoadBtnDisable();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Load Game Data Failed, no Game Instance"));
		}
		// =========================================
	}
}

void AKHIGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
