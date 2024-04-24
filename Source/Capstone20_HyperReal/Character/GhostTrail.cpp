// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostTrail.h"

// Sets default values
AGhostTrail::AGhostTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	SetRootComponent(m_Mesh);

	// 고스트 머티리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MtrlAsset(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/Material/MT_GhostTrailSoldier.MT_GhostTrailSoldier'"));

	if (MtrlAsset.Succeeded())
		m_pGhostMaterial = MtrlAsset.Object;

	m_fLifeTime = 0.5f;
	m_eGhostType = EGhostTrailType::Fade;

	m_fFadeTime = 0.5f;
	m_fAccFadeTime = 0.f;
}

// Called when the game starts or when spawned
void AGhostTrail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime -= DeltaTime;

	if (m_fLifeTime <= 0.f)
	{
		switch (m_eGhostType)
		{
		case EGhostTrailType::LifeSpan:
			Destroy();
			break;
		case EGhostTrailType::Fade:
		{
			m_fAccFadeTime += DeltaTime;

			float fOpacity = 1.f - (m_fAccFadeTime / m_fFadeTime);

			if (fOpacity <= 0.f)
				Destroy();

			for (auto& mtrl : m_arrGhostMaterial)
			{
				mtrl->SetScalarParameterValue(TEXT("Opacity"), fOpacity);
			}
		}
			break;
		}
	}
}

void AGhostTrail::SetMesh(const FString& _strPath)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(), *_strPath);

	if (Mesh)
		m_Mesh->SetSkeletalMesh(Mesh);

	// 재질 생성
	int32 iMtrlCount = m_Mesh->GetNumMaterials();

	for (int32 i = 0; i < iMtrlCount; i++)
	{
		UMaterialInstanceDynamic* Mtrl = m_Mesh->CreateDynamicMaterialInstance(i, m_pGhostMaterial);
		m_arrGhostMaterial.Add(Mtrl);
	}
}

void AGhostTrail::SetMesh(USkeletalMesh* _pMesh)
{
	if (_pMesh)
		m_Mesh->SetSkeletalMesh(_pMesh);

	// 재질 생성
	int32 iMtrlCount = m_Mesh->GetNumMaterials();

	for (int32 i = 0; i < iMtrlCount; i++)
	{
		UMaterialInstanceDynamic* Mtrl = m_Mesh->CreateDynamicMaterialInstance(i, m_pGhostMaterial);
		m_arrGhostMaterial.Add(Mtrl);
	}
}

void AGhostTrail::CopyAnimation(USkeletalMeshComponent* _pCom)
{
	m_Mesh->CopyPoseFromSkeletalComponent(_pCom);
}

