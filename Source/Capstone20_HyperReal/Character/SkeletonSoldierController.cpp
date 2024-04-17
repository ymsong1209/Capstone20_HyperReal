// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSoldierController.h"
#include "SkeletonSoldierController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "SkeletonSoldier.h"

ASkeletonSoldierController::ASkeletonSoldierController()
{
}

void ASkeletonSoldierController::OnClickMoveTriggered()
{
	Super::OnClickMoveTriggered();

	// Move towards mouse pointer or touch
	ASkeletonSoldier* pSoldier = Cast<ASkeletonSoldier>(GetPawn());

	// 만약 훨윈드 중이면 추가 이동 가능하게 구현
	if ((pSoldier->GetUsingSkill() == EPlayerSkill::SkillA))
	{
		FVector WorldDirection = (CachedDestination - pSoldier->GetActorLocation()).GetSafeNormal();
		pSoldier->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ASkeletonSoldierController::OnClickMoveReleased()
{
	Super::OnClickMoveReleased();

	// Move towards mouse pointer or touch
	ASkeletonSoldier* pSoldier = Cast<ASkeletonSoldier>(GetPawn());

	if (pSoldier->GetUsingSkill() != EPlayerSkill::SkillA)
		return;

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}
