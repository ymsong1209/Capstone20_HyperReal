// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "Rune.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE20_HYPERREAL_API URune : public UObject
{
	GENERATED_BODY()
	
protected:
	// 룬 이미지
	UTexture2D* m_TexRune;

	// 룬 이름
	FString m_strName;

	// 룬 설명
	FString m_strDesc;

	ERuneType m_eRuneType;

	int32 m_iLevel;

	// 생명 추가 계수
	float m_fHealthRatio;

	// 마나 추가 계수
	float m_fSoulRatio;

	// 공격 추가 계수
	float m_fAttackRatio;

	float m_fAttackSpeedRatio;

	float m_fMoveSpeedRatio;

	float m_fCoolDownRatio;

	// 지속시간, 반격 대미지 등 기타 계수
	float m_fEtc;

	float m_fAccCoolTime;
	float m_fCoolTime;

public:
	UTexture2D* GetIconImage() { return m_TexRune; }
	const FString& GetName() { return m_strName; }
	const FString& GetExplan() { return m_strDesc; }

	ERuneType GetRuneType() { return m_eRuneType; }

	int32 GetLevel() { return m_iLevel; }
	void SetLevel(int32 _iLevel) { m_iLevel = _iLevel; }
	float GetHealthRatio() { return 1.f + m_fHealthRatio; }
	float GetSoulRatio() { return 1.f + m_fSoulRatio; }
	float GetAttackRatio() { return 1.f + m_fAttackRatio; }
	float GetAttackSpeedRatio() { return 1.f + m_fAttackSpeedRatio; }
	float GetMoveSpeedRatio() { return 1.f + m_fMoveSpeedRatio; }
	float GetCoolDownRatio() { return 1.f - m_fCoolDownRatio; }
	float GetExtraValue() { return m_fEtc; }

public:
	URune();

public:
	// 공격과 관련된 함수
	virtual void GiveDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) {};
	virtual void NormalAttackTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) {};
	virtual void TakeDamageTrigger(AActor* _pActor = nullptr, float _fValue = 0.f) {};
	virtual void Activate(AActor* _pActor = nullptr, float _fValue = 0.f) {};

public:
	void Updgrade();
};
