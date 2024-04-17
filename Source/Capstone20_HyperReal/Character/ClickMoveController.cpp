// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickMoveController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "PlayerCharacter.h"

AClickMoveController::AClickMoveController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AClickMoveController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AClickMoveController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickMoveAction, ETriggerEvent::Started, this, &AClickMoveController::OnInputStarted);
		EnhancedInputComponent->BindAction(ClickMoveAction, ETriggerEvent::Triggered, this, &AClickMoveController::OnClickMoveTriggered);
		EnhancedInputComponent->BindAction(ClickMoveAction, ETriggerEvent::Completed, this, &AClickMoveController::OnClickMoveReleased);
		EnhancedInputComponent->BindAction(ClickMoveAction, ETriggerEvent::Canceled, this, &AClickMoveController::OnClickMoveReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AClickMoveController::OnInputStarted()
{
	StopMovement();
}

void AClickMoveController::OnClickMoveTriggered()
{	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APlayerCharacter* ControlledPawn = Cast<APlayerCharacter>(GetPawn());
	
	if (ControlledPawn != nullptr && !ControlledPawn->OnAttack() && (ControlledPawn->GetUsingSkill() == EPlayerSkill::None))
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AClickMoveController::OnClickMoveReleased()
{
	// Move towards mouse pointer or touch
	APlayerCharacter* ControlledPawn = Cast<APlayerCharacter>(GetPawn());

	if (ControlledPawn->OnAttack() || (ControlledPawn->GetUsingSkill() != EPlayerSkill::None))
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