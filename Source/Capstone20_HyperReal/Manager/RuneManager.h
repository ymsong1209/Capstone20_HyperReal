// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RuneManager.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API URuneManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	class URune* m_arrRune[(int32)ERuneType::End];

public:

public:
	URuneManager();
	~URuneManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Init();

public:
	URune* GetRune(ERuneType _eType) { return m_arrRune[(int)_eType]; }

	void GiveDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f);
	void NormalAttackTrigger(AActor* _pActor = nullptr, float _fValue = 0.f);
	void TakeDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f);
	void Activate(AActor* _pActor = nullptr, float _fValue = 0.f);

public:
	float GetHealthAdd();
	float GetSoulAdd();
	float GetAttackAdd();
	float GetAttackSpeedAdd();
	float GetMoveSpeedAdd();
	float GetCoolDownAdd();

	void UpgradeRune(ERuneType _eType);
};
