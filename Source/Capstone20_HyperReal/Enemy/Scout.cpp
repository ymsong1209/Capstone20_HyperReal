// Fill out your copyright notice in the Description page of Project Settings.


#include "Scout.h"
#include "MonsterAnimInstance.h"
#include "../Projectile/ScoutArrow.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AScout::AScout()
{
	// 코드로 캐릭터 메쉬 세팅
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

	// animationBP 레퍼런스 받을때 _C를 사용해야함
	static ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Monster/Scout/ABP_Scout.ABP_Scout_C'"));
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

void AScout::Attack()
{
	Super::Attack();
	FVector Loc = GetActorLocation() + GetActorForwardVector() * 100.f;
	
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AScoutArrow* ArrowActor = GetWorld()->SpawnActor<AScoutArrow>(Loc, GetActorRotation(), param);
	if(!ArrowActor) return;
	ArrowActor->SetOwnerController(GetController());
	ArrowActor->SetDamage(static_cast<float>(mInfo.Attack));
	
	//AIController를 이용해 Blackboard에 있는 target을 얻어옴
	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		AActor* Target = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
		// //유도탄
		// if(Target)
		// {
		// 	ArrowActor->SetTarget(Target);
		// }
	}
	
}
