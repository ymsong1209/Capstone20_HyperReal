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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* m_ASWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UMaterialInterface* m_pBlinkOverlayInterface;

	// 무기 표현용 스켈레탈 매쉬(트레일을 구현하기 위함)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* m_WeaponMesh;

protected:
	UMaterialInstanceDynamic* m_MIDBlinkOverlay;

public:
	UMaterialInstanceDynamic* GetMIDOverlay() { return m_MIDBlinkOverlay; }
	void SwitchBlinkOverlay(bool _bSwitch);

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
