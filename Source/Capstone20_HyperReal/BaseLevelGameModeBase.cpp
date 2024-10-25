// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelGameModeBase.h"
#include "Character/SkeletonSoldierController.h"
#include "Character/SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/BaseLevelWidget.h"
#include "GameFramework/PlayerController.h"
ABaseLevelGameModeBase::ABaseLevelGameModeBase()
{
	//static ConstructorHelpers::FClassFinder<UBaseLevelWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/UI_BaseLevel.UI_BaseLevel_C'"));
	static ConstructorHelpers::FClassFinder<UBaseLevelWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_SYMContent/UI/UI_BaseLevel_SYM.UI_BaseLevel_SYM_C'"));
	if (WidgetClass.Succeeded())
	{
		mBaseLevelWidgetClass = WidgetClass.Class;
	}
}

#include "CapStoneGameInstance.h"
#include "Manager/PlayerManager.h"
void ABaseLevelGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//{
	//	// ========================================
	//	// 플레이어 데이터 로드용 테스트 코드 - 서종원
	//	UCapStoneGameInstance* pGameInst = Cast<UCapStoneGameInstance>(GetGameInstance());

	//	if (pGameInst)
	//	{
	//		pGameInst->LoadGameData();
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Load Game Data Failed, no Game Instance"));
	//	}
	//	// =========================================
	//}
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
		{
			mBaseLevelWidget->AddToViewport();
			mBaseLevelWidget->RefreshBaseCampMagicWidget();
		}
	}
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// 마우스 커서 표시
		PlayerController->bShowMouseCursor = true;

		// 마우스 입력 비활성화
		PlayerController->SetIgnoreLookInput(true);
		PlayerController->SetIgnoreMoveInput(true);

		// 입력 모드를 UI 전용으로 설정
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
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

