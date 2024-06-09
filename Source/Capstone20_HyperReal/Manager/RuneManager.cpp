// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneManager.h"
#include "../Item/Rune/Rune.h"
#include "../Item/Rune/RotationRune.h"
#include "../Item/Rune/LightningRune.h"
#include "../Item/Rune/ExtremeRune.h"
#include "../Item/Rune/DemolitionRune.h"
#include "../Item/Rune/DashRune.h"
#include "../Item/Rune/DrainRune.h"
#include "../Item/Rune/HasteRune.h"
#include "../Item/Rune/ThornRune.h"
#include "../Item/Rune/DistortionRune.h"
#include "../Item/Rune/ResurrectionRune.h"

URuneManager::URuneManager()
{
}

URuneManager::~URuneManager()
{
}

void URuneManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Init();
}

void URuneManager::Deinitialize()
{
	Super::Deinitialize();
}

void URuneManager::Init()
{
	// 룬 초기화
	m_arrRune[(int)ERuneType::Rotation] = NewObject<URotationRune>(this, URotationRune::StaticClass());
	m_arrRune[(int)ERuneType::Lightning] = NewObject<ULightningRune>(this, ULightningRune::StaticClass());
	m_arrRune[(int)ERuneType::Extreme] = NewObject<UExtremeRune>(this, UExtremeRune::StaticClass());
	m_arrRune[(int)ERuneType::Demolition] = NewObject<UDemolitionRune>(this, UDemolitionRune::StaticClass());
	m_arrRune[(int)ERuneType::Dash] = NewObject<UDashRune>(this, UDashRune::StaticClass());
	m_arrRune[(int)ERuneType::Drain] = NewObject<UDrainRune>(this, UDrainRune::StaticClass());
	m_arrRune[(int)ERuneType::Haste] = NewObject<UHasteRune>(this, UHasteRune::StaticClass());
	m_arrRune[(int)ERuneType::Thorn] = NewObject<UThornRune>(this, UThornRune::StaticClass());
	m_arrRune[(int)ERuneType::Distortion] = NewObject<UDistortionRune>(this, UDistortionRune::StaticClass());
	m_arrRune[(int)ERuneType::Resurrection] = NewObject<UResurrectionRune>(this, UResurrectionRune::StaticClass());

	// 만약 저장 데이터가 있다면 레벨을 바꿔줘야함
}

void URuneManager::GiveDamageTrigger(AActor* _pActor, float _fValue)
{
	for (URune* rune : m_arrRune)
	{
		if (IsValid(rune))
			rune->GiveDamageTrigger(_pActor, _fValue);
	}
}

void URuneManager::NormalAttackTrigger(AActor* _pActor, float _fValue)
{
	


	for (URune* rune : m_arrRune)
	{
		if(IsValid(rune))
			rune->NormalAttackTrigger(_pActor, _fValue);
	}
}

void URuneManager::TakeDamageTrigger(AActor* _pActor, float _fValue)
{
	for (URune* rune : m_arrRune)
	{
		if (IsValid(rune))
			rune->TakeDamageTrigger(_pActor, _fValue);
	}
}

void URuneManager::Activate(AActor* _pActor, float _fValue)
{
	for (URune* rune : m_arrRune)
	{
		if (IsValid(rune))
			rune->TakeDamageTrigger(_pActor, _fValue);
	}
}
