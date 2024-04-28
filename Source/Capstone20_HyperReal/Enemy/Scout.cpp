// Fill out your copyright notice in the Description page of Project Settings.


#include "Scout.h"
#include "MonsterAnimInstance.h"

AScout::AScout()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ڵ�� ĳ���� �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Characters_Prebuilt/Units/SK_Scout.SK_Scout'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMesh setting failed"));
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -55.f));
	GetMesh()->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// animationBP ���۷��� ������ _C�� ����ؾ���
	static ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Monster/ABP_Scout.ABP_Scout_C'"));
	if (AnimClass.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Setting Failed"));
	}

	mDataTableKey = TEXT("Scout");
}

void AScout::BeginPlay()
{
	Super::BeginPlay();
}

void AScout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
