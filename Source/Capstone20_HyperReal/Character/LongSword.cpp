// Fill out your copyright notice in the Description page of Project Settings.


#include "LongSword.h"

ALongSword::ALongSword()
{
	// 트레일용 애니메이션 시퀀스
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimAsset(TEXT("/Script/Engine.AnimSequence'/Game/A_SJWContent/Weapon/Animation/AS_LongSwordTrail.AS_LongSwordTrail'"));

	if (AnimAsset.Succeeded())
		m_ASWeapon = AnimAsset.Object;

	// 롱소드용 매쉬 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/A_SJWContent/Weapon/SK_LongSword.SK_LongSword'"));

	if (MeshAsset.Succeeded())
		m_WeaponMesh->SetSkeletalMesh(MeshAsset.Object);

	m_WeaponMesh->SetRelativeScale3D(FVector(2.f, 2.f, 3.f));
}

void ALongSword::BeginPlay()
{
	Super::BeginPlay();

	m_WeaponMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
}
