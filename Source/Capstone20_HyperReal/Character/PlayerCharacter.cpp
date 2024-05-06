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
#include "GhostTrail.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
APlayerCharacter::APlayerCharacter() :
	DefaultMappingContext(nullptr),
	AttackAction(nullptr),
	m_pAnim(nullptr),
	m_iAttackMontageIndex(0),
	m_bOnAttack(false),
	m_bComboDetected(false),
	m_eUsingSkill(EPlayerSkill::None),
	m_fAttackImpulse(0.f),
	m_fAnimPlaySpeed(1.f),
	m_fGhostTrailTickTime(0.1f),
	m_bGhostTrail(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

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
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	m_fDefaultSpeed = GetCharacterMovement()->MaxWalkSpeed;
	m_fDefaultAccel = GetCharacterMovement()->MaxAcceleration;
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

	if (m_bGhostTrail)
	{
		m_fAccGhostTime += DeltaTime;

		if (m_fAccGhostTime >= m_fGhostTrailTickTime)
		{
			m_fAccGhostTime -= m_fGhostTrailTickTime;

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AGhostTrail* pGhost = GetWorld()->SpawnActor<AGhostTrail>(
				AGhostTrail::StaticClass(),
				GetMesh()->GetComponentLocation(),
				GetMesh()->GetComponentRotation(), param);

			pGhost->SetMesh(m_SKMesh);
			pGhost->CopyAnimation(GetMesh());
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(pInput))
	{
		// 우클릭을 기본 공격에 바인딩 추후 triggerd 로 바꾸는게 좀더 자연스러울듯함
		pInput->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		// 스킬은 직업 마다 다를 수 있으므로 재정의해서 구현
	}
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void APlayerCharacter::Attack()
{
	if (m_bOnAttack || (m_eUsingSkill != EPlayerSkill::None))
	{
		if (!m_bComboDetected)
			m_bComboDetected = true;

		return;
	}

	m_bOnAttack = true;
	m_bComboDetected = false;

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

		FVector vDir = (CachedDestination - GetActorLocation());
		vDir.Z = 0.f;
		vDir = vDir.GetSafeNormal();
		SetActorRotation(vDir.Rotation());
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->AddImpulse(GetActorForwardVector() * m_fAttackImpulse, true);
}

void APlayerCharacter::AttackCombo()
{
	m_iAttackMontageIndex = (m_iAttackMontageIndex + 1) % m_arrAttackMontage.Num();
	m_bComboDetected = false;
}

void APlayerCharacter::AttackEnd()
{
	m_iAttackMontageIndex = 0;
	m_bOnAttack = false;
	m_bComboDetected = false;
}

void APlayerCharacter::AttackReset()
{
	m_bOnAttack = false;
	m_bComboDetected = false;
	Attack();
}

FVector APlayerCharacter::GetMousePosition()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	AClickMoveController* pController = Cast<AClickMoveController>(GetController());

	bHitSuccessful = pController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	FVector CachedDestination;

	// If we hit a surface, cache the location
	if (bHitSuccessful)
		CachedDestination = Hit.Location;

	return CachedDestination;
}

void APlayerCharacter::ChangeWalkSpeed(float _value)
{
	GetCharacterMovement()->MaxWalkSpeed = (m_fDefaultSpeed * _value);
	GetCharacterMovement()->MaxAcceleration = (m_fDefaultAccel * _value);
}
