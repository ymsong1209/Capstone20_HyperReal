// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Enemy_BaseWeapon.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn parameters 설정
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; // 이 액터를 오너로 설정
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Weapon = GetWorld()->SpawnActor<AEnemy_BaseWeapon>(EnemyWeaponClass);
	Weapon = GetWorld()->SpawnActor<AEnemy_BaseWeapon>(EnemyWeaponClass, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParams);
	if (Weapon) {
		UE_LOG(LogTemp, Display, TEXT("Weapon Spawned"));
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("sheath"));
		Weapon->SetOwner(this);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Spawned"));
	}

}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::AttackMelee()
{
	UE_LOG(LogTemp, Display, TEXT("AttackMelee Called"));
}

void ABaseEnemy::SpawnFinished()
{
	if (Weapon) {
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r_sword"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Spawned"));
	}

}
