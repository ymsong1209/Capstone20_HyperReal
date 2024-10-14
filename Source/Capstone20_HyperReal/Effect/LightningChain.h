// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "LightningChain.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API ALightningChain : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* m_Lightning;

private:
	int32 m_iChainCount;
	float m_fRange;
	AActor* m_Target;
	TArray<AActor*> m_arrTarget;
	float m_fDamage;

	class AEffectBase* m_pCurLightEffect;

	FTimerHandle m_hSpawnTimerHandle;
	FVector m_vPrevLoc;

public:
	void SetChainCount(int32 _iCount) { m_iChainCount = _iCount; }
	void SetTarget(AActor* _pTarget) { m_Target = _pTarget; }
	void SetDamage(float _fDmg) { m_fDamage = _fDmg; }

public:	
	// Sets default values for this actor's properties
	ALightningChain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void CheckAndSpawn();
	void FindNewTarget();
	void SpawnLightning();
	void SpawnHitEffect(FVector _vLoc, FRotator _vRot);

};
