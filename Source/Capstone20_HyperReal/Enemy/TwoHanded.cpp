// Fill out your copyright notice in the Description page of Project Settings.
#include "TwoHanded.h"
#include "MonsterAnimInstance.h"

ATwoHanded::ATwoHanded()
{
	// 코드로 캐릭터 메쉬 세팅
	// preview에서 swordman으로 보일 것이고, beginplay에서 랜덤하게 캐릭터가 바뀜.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Toony_Tiny_RTS_Set_UE5/Meshes/Characters_Prebuilt/Units/SK_HeavySwordman.SK_HeavySwordman'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMesh setting failed"));
	}
	
	// animationBP 레퍼런스 받을때 _C를 사용해야함
	static ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SYMContent/Monster/TwoHanded/ABP_TwoHanded.ABP_TwoHanded_C'"));
	if (AnimClass.Succeeded()) {
		
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
		mHead->SetAnimInstanceClass(AnimClass.Class);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Setting Failed"));
	}
		
	mDataTableKey = TEXT("TwoHanded");
}

void ATwoHanded::BeginPlay()
{
	Super::BeginPlay();
}

void ATwoHanded::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATwoHanded::Attack()
{
	Super::Attack();
	FVector Start = GetActorLocation() + GetActorForwardVector();
	FVector End = GetActorLocation() + GetActorForwardVector() * (mInfo.AttackDistance);

	FCollisionQueryParams params(NAME_None, false, this);

	FHitResult result;
	bool Hit = GetWorld()->SweepSingleByChannel(result,Start,End, FQuat::Identity,
		ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(50.f), params);

	if(Hit)
	{
		if(result.GetActor()->TakeDamage(mInfo.Attack, FDamageEvent(),
			GetController(), this) == -1.f)
		{
			
		}
		
	}
#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End)/ 2.f, mInfo.AttackDistance / 2.f, 50.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);
#endif
}
