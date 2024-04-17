// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_BaseWeapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemy_BaseWeapon::AEnemy_BaseWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AEnemy_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


