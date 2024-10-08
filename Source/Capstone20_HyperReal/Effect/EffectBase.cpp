// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()	:
	m_bOnceDestroy(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	SetRootComponent(m_Niagara);
	m_Particle->SetupAttachment(RootComponent);
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

bool AEffectBase::SetParticle(const FString& Path)
{
	UParticleSystem* Asset = LoadObject<UParticleSystem>(nullptr, *Path);
	if(Asset)
	{
		m_Particle->SetTemplate(Asset);
		m_Particle->OnSystemFinished.AddDynamic(this, &AEffectBase::ParticleFinish);
		return true;
	}
	return false;
}

bool AEffectBase::SetParticle(UParticleSystem* Particle)
{
	if(Particle)
	{
		m_Particle->SetTemplate(Particle);
		m_Particle->OnSystemFinished.AddDynamic(this, &AEffectBase::ParticleFinish);
		return true;
	}
	return false;
}

bool AEffectBase::SetSound(const FString& Path, float volume)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);
	if(Sound)
	{
		m_Sound = Sound;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound, GetActorLocation(), volume);
		return true;
	}
	return false;
}

bool AEffectBase::SetSound(USoundBase* Sound, float volume)
{
	if(Sound)
	{
		m_Sound = Sound;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound, GetActorLocation(), volume);
		return true;
	}
	return false;
}

void AEffectBase::SetOnceDestroy(bool _bSet)
{
	m_bOnceDestroy = _bSet;

	if (_bSet)
	{
		if (m_Niagara)
			m_Niagara->OnSystemFinished.AddDynamic(this, &AEffectBase::NiagaraFinish);
		else if(m_Particle)
			m_Particle->OnSystemFinished.AddDynamic(this, &AEffectBase::ParticleFinish);
	}
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
	if(m_bOnceDestroy)
		Destroy();
}

void AEffectBase::ParticleFinish(UParticleSystemComponent* Particle)
{
	if (m_bOnceDestroy)
		Destroy();
}

