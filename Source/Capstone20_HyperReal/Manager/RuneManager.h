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
private:
};
