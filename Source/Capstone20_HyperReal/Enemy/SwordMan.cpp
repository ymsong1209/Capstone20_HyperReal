// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMan.h"
#include "MonsterAnimInstance.h"


// Sets default values
ASwordMan::ASwordMan()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 코드로 캐릭터 메쉬 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Characters_Prebuilt/Units/SK_Swordman.SK_Swordman'"));
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
	static ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Monster/ABP_SwordMan.ABP_SwordMan_C'"));
	if (AnimClass.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Setting Failed"));
	}
		
	mDataTableKey = TEXT("SwordMan");
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

void ASwordMan::Attack()
{
	Super::Attack();
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = GetActorLocation() + GetActorForwardVector() * (50.f + mInfo.AttackDistance);

	FCollisionQueryParams params(NAME_None, false, this);

	FHitResult result;
	bool Hit = GetWorld()->SweepSingleByChannel(result,Start,End, FQuat::Identity,
		ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(50.f), params);

	if(Hit)
	{
		// FActorSpawnParameters param;
		// param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//
		// AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
		// 	result.ImpactPoint,
		// 	result.ImpactNormal.Rotation()(), param);
		//
		// Effect->SetParticle(TEXT(""));
		// Effect->SetSound(TEXT(""));

		if(result.GetActor()->TakeDamage(mInfo.Attack, FDamageEvent(),
			GetController(), this) == -1.f)
		{
			
		}
		
	}
#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End)/ 2.f, mInfo.AttackDistance, 50.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);
#endif
}
