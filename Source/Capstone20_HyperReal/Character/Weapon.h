// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* m_ASWeapon;

protected:
	// 무기 표현용 스켈레탈 매쉬(트레일을 구현하기 위함)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void StartTrail();
	void EndTrail();
};
