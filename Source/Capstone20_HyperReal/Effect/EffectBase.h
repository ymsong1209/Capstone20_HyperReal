// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EffectBase.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	UNiagaraComponent* m_Niagara;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"), Category = "Effect")
	UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"), Category = "Effect")
	USoundBase* m_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	bool m_bOnceDestroy;

public:
	bool SetNiagara(const FString& _strPath);
	bool SetNiagara(UNiagaraSystem* _pNiagara);
	bool SetParticle(const FString& Path);
	bool SetParticle(UParticleSystem* Particle);
	bool SetSound(const FString& Path, float volume = 1.f);
	bool SetSound(USoundBase* Sound, float volume = 1.f);

	void SetOnceDestroy(bool _bSet);

	UNiagaraComponent* GetNiagaraCom() { return m_Niagara; }

	FVector GetNiagaraComScale();
	void SetNiagaraComScale(FVector _vScale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void NiagaraFinish(UNiagaraComponent* _pCom);
	UFUNCTION()
	void ParticleFinish(UParticleSystemComponent* Particle);

};
