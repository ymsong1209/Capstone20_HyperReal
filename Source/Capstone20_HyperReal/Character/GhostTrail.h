// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GhostTrail.generated.h"


UENUM()
enum class EGhostTrailType : uint8
{
	LifeSpan,
	Fade
};

UCLASS()
class CAPSTONE20_HYPERREAL_API AGhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostTrail();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPoseableMeshComponent* m_Mesh;

	UMaterialInterface* m_pGhostMaterial;
	TArray<UMaterialInstanceDynamic*> m_arrGhostMaterial;

	EGhostTrailType m_eGhostType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_fLifeTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_fFadeTime;

	float m_fAccFadeTime;

public:
	void SetGhostType(EGhostTrailType _eType) { m_eGhostType = _eType; }
	void SetLifeTime(float _fTime) { m_fLifeTime = _fTime; }
	void SetFadeTime(float _fTime) { m_fFadeTime = _fTime; }
	void SetColorParam(FVector& _vColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh(const FString& _strPath);
	void SetMesh(USkeletalMesh* _pMesh);
	void CopyAnimation(USkeletalMeshComponent* _pCom);

};
