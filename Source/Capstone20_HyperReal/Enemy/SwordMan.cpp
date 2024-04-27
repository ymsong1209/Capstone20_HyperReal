// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMan.h"
#include "MonsterAnimInstance.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASwordMan::ASwordMan()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 코드로 캐릭터 메쉬 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Characters_Prebuilt/Units/SK_Swordman.SK_Swordman'"));
	if (MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMesh setting complete"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMesh setting failed"));
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -55.f));
	GetMesh()->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// animationBP 레퍼런스 받을때 _C를 사용해야함
	static ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Monster/ABP_SwordMan.ABP_SwordMan_C'"));
	if (AnimClass.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Setting complete"));
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Setting failed"));
	}
		

}

// Called when the game starts or when spawned
void ASwordMan::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASwordMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
