// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "PlayerAnimInstance.h"
#include "ClickMoveController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "ClickMoveController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()	:
	DefaultMappingContext(nullptr),
	AttackAction(nullptr),
	m_pAnim(nullptr),
	m_iAttackMontageIndex(0),
	m_bOnAttack(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 애님 인스턴스 세팅
	m_pAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// 컨트롤러에 인풋 컨텍스트 설정
	AClickMoveController* pController = Cast<AClickMoveController>(GetController());
	
	if (IsValid(pController))
	{
		UEnhancedInputLocalPlayerSubsystem* pSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pController->GetLocalPlayer());

		if (IsValid(pSubSystem))
			pSubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(pInput))
	{
		pInput->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}
}

void APlayerCharacter::Attack()
{
	m_bOnAttack = true;

	// 마우스 방향으로 회전
	FHitResult Hit;
	bool bHitSuccessful = false;

	AClickMoveController* pController = Cast<AClickMoveController>(GetController());

	if (IsValid(pController))
	{
		bHitSuccessful = pController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		FVector CachedDestination;

		// If we hit a surface, cache the location
		if (bHitSuccessful)
			CachedDestination = Hit.Location;

		FVector vDir = (CachedDestination - GetActorLocation()).GetSafeNormal();
		SetActorRotation(vDir.Rotation());
	}

	// 움직임 제거(공격이 끝나면 풀어야함)
	GetCharacterMovement()->StopMovementImmediately();
}

void APlayerCharacter::AttackEnd()
{
	m_iAttackMontageIndex = 0;
	UCharacterMovementComponent* pMovement = GetCharacterMovement();
}
