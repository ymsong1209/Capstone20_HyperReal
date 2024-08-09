// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAttack.h"
#include "../Character/PlayerCharacter.h"
#include "../Building/BossAttackProjectile.h"


// Sets default values
ABossAttack::ABossAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Decal box생성
	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("BuildingDecal"));
	mDecal->SetupAttachment(RootComponent);
	mDecal->SetRelativeLocation(FVector(0, 200, 0));  // 위치 조정
	mDecal->SetRelativeRotation(FRotator(-90, 180, 0));  // 바닥에 평행하도록 회전
	mDecal->DecalSize = FVector(150, 150, 150);  // 데칼 크기 설정 (길이, 너비, 높이)
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SYMContent/Building/MT_PortalDecal_Inst.MT_PortalDecal_Inst'"));
	if (DecalMaterial.Succeeded())
	{
		mDecal->SetDecalMaterial(DecalMaterial.Object);
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("DecalMaterial not found"));
	}
	
	mDecalAdjustTime = -1.f;
	mAttackWaitTime = -1.f;
	mAccDecalAdjustTime = 0.f;
	mAccAttackTime = 0.f;
}

// Called when the game starts or when spawned
void ABossAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(mDecalAdjustTime == -1.f || mAttackWaitTime == -1.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("mAttackTime is -1"));
		Destroy();
	}

	AdjustDecal(DeltaTime);
	FollowPlayer();
	if(mDecalAdjustTime <= mAccDecalAdjustTime)
	{
		mAccAttackTime += DeltaTime;
		if(mAccAttackTime >= mDecalAdjustTime + mAttackWaitTime)
		{
			SpawnProjectile();
			Destroy();
		}
	}
	
}

void ABossAttack::AdjustDecal(float Deltatime)
{
	if(!IsValid(mDecal)) return;
	//mDecalAdjustTime의 시간동안 크기를 늘렸다가 줄임.
	mAccDecalAdjustTime += Deltatime;
	// 주기적인 크기 변화를 위해 sin 함수를 사용
	float scaleValue = FMath::Sin((mAccDecalAdjustTime / mDecalAdjustTime) * PI * 2.0f);

	// scaleValue는 -1에서 1까지 변하기 때문에 이를 0.5 ~ 1.5로 변환
	float adjustedScale = FMath::Lerp(0.5f, 1.5f, (scaleValue + 1.0f) * 0.5f);

	// Decal의 크기 조절
	mDecal->SetRelativeScale3D(FVector(adjustedScale));
}

void ABossAttack::FollowPlayer()
{
	if(mDecalAdjustTime == -1.f || mAttackWaitTime == -1.f) return;
	if(mDecalAdjustTime <= mAccDecalAdjustTime) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!IsValid(Player)) return;
	
	//player위치로 이동
	//player의 높이의 절반만큼 땅에 파묻음
	FVector PlayerLoc = Player->GetActorLocation();
	PlayerLoc.Z -= Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	SetActorLocation(PlayerLoc);
}

void ABossAttack::SpawnProjectile()
{
	float HeightOffset = 400.0f;  // 스폰 위치의 Z 오프셋 (위로 300 units)
	FVector Loc = GetActorLocation() + FVector(0.0f, 0.0f, HeightOffset);
	FActorSpawnParameters param;
	
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	ABossAttackProjectile* ProjectileActor = GetWorld()->SpawnActor<ABossAttackProjectile>(Loc, GetActorRotation(), param);
	if(!IsValid(ProjectileActor)) return;
	ProjectileActor->SetOwnerController(GetInstigatorController());
	ProjectileActor->SetDamage(static_cast<float>(mDamage));
}


