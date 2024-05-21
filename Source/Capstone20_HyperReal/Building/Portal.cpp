// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "../Character/PlayerCharacter.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"

APortal::APortal()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Low_Poly_Viking_World/Models/Constructions/SM_Small_House_03_A.SM_Small_House_03_A'"));
	if (BuildingMeshAsset.Succeeded())
	{
		BuildingMesh->SetStaticMesh(BuildingMeshAsset.Object);
	}
	BuildingMesh->bReceivesDecals = false;
	
	//Decal box생성
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("BuildingDecal"));
	Decal->SetupAttachment(RootComponent);
	Decal->SetRelativeLocation(FVector(0, 200, 0));  // 위치 조정
	Decal->SetRelativeRotation(FRotator(-90, 180, 0));  // 바닥에 평행하도록 회전
	Decal->DecalSize = FVector(150, 150, 150);  // 데칼 크기 설정 (길이, 너비, 높이)
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SYMContent/Building/MT_PortalDecal_Inst.MT_PortalDecal_Inst'"));
	if (DecalMaterial.Succeeded())
	{
		Decal->SetDecalMaterial(DecalMaterial.Object);
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("DecalMaterial not found"));
	}
	
	// Collider 생성
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(TEXT("Portal"));
	Collider->SetupAttachment(Decal);  // Decal에 Collider 부착
	Collider->InitBoxExtent(Decal->DecalSize);
	
	// Bind the overlap event
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Check if the OtherActor is a player character
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
		if (PlayerController)
		{
			PlayerCharacter->SetInvincible(true);
			PlayerCharacter->SetPortal(this);

			AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
			if(GameMode)
			{
				UInGameUserWidget* widget = GameMode->GetInGameWidget();
				if (widget)
				{
					int gold = PlayerCharacter->m_Info.LevelAccGold;
					int building = 0;
					int enemy = 0;
					widget->OpenRewardUI(gold, building, enemy);
					UGameplayStatics::SetGamePaused(GetWorld(), true);
				}
			}
		}
	}
}

void APortal::TransitionToNextLevel(AActor* OtherActor)
{
	// Check if the OtherActor is a player character
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	// Start fade to black
	PlayerController->PlayerCameraManager->StartCameraFade(0.f, 1.f, 1.f, FColor::Black, false, true);

	// After fade complete, transition to next level
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &APortal::OpenLevel, 1.f, false);
}

void APortal::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, FName("KHIStartMap"));
}
