// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()	:
	m_bOnceDestory(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));

	SetRootComponent(m_Niagara);
}

bool AEffectBase::SetNiagara(const FString& _strPath)
{
	UNiagaraSystem* Asset = LoadObject<UNiagaraSystem>(nullptr, *_strPath);

	if (Asset)
	{
		m_Niagara->SetAsset(Asset);

		m_Niagara->OnSystemFinished.AddDynamic(this, &AEffectBase::NiagaraFinish);
		return true;
	}

	return false;
}

bool AEffectBase::SetNiagara(UNiagaraSystem* _pNiagara)
{
	if (_pNiagara)
	{
		m_Niagara->SetAsset(_pNiagara);

		m_Niagara->OnSystemFinished.AddDynamic(this, &AEffectBase::NiagaraFinish);
		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::NiagaraFinish(UNiagaraComponent* _pCom)
{
	Destroy();
}

