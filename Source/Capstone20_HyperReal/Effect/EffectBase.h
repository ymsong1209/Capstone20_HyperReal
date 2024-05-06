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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* m_Niagara;
	
	bool m_bOnceDestory;

public:
	bool SetNiagara(const FString& _strPath);
	bool SetNiagara(UNiagaraSystem* _pNiagara);

	void SetOnceDestory(bool _bSet) { m_bOnceDestory = _bSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void NiagaraFinish(UNiagaraComponent* _pCom);

};
