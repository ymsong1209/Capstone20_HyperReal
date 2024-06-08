// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneManager.h"
#include "../Item/Rune/Rune.h"

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
}
