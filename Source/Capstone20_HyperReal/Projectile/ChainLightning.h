// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ChainLightning.generated.h"

class AEffectBase;
/**
 LightningChain 액터로 기능을 변경하였기 때문에 사용하지 않는 클래스임
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API AChainLightning : public AProjectileBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* m_Lightning;

private:
	int32 m_iChainCount;

	TArray<AActor*> m_arrTarget;

	float m_fRange;

	AEffectBase* m_pCurrentLight;

public:
	void SetChainCount(int32 _iCount) { m_iChainCount = _iCount; }

public:
	// Sets default values for this actor's properties
	AChainLightning();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void FindNewTarget();
	void SpawnLightning();

};
