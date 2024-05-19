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
#include "../CapStoneGameInstance.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
APlayerCharacter::APlayerCharacter() :
	DefaultMappingContext(nullptr),
	AttackAction(nullptr),
	m_iAttackMontageIndex(0),
	m_fAttackImpulse(0.f),
	m_fGhostTrailTickTime(0.1f),
	m_pAnim(nullptr),
	m_bOnAttack(false),
	m_bComboDetected(false),
	m_eUsingSkill(EPlayerSkill::None),
	m_fAnimPlaySpeed(1.f),
	m_bGhostTrail(false),
	m_bInvincible(false)
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

	// 캐릭터 이펙트용 나이아가라 컴포넌트 추가(필요시 배열로 변경해도 됨)
	m_NSEffect01 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara01"));
	m_NSEffect01->SetupAttachment(RootComponent);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	m_fDefaultSpeed = GetCharacterMovement()->MaxWalkSpeed;
	m_fDefaultAccel = GetCharacterMovement()->MaxAcceleration;

	// 무적 판정, 차징 등등에 쓰일 깜빡이는 오버레이 머티리얼 로딩
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MIBlinkOverlay(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/Material/MTI_BlinkFresnel.MTI_BlinkFresnel'ddd"));
	if (MIBlinkOverlay.Succeeded())
	{
		m_pBlinkOverlayInterface = MIBlinkOverlay.Object;
		m_MIDBlinkOverlay = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), m_pBlinkOverlayInterface);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	// ESP 효과용 커스텀 뎁스 패스 활성화 코드
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = 100;

	if (IsValid(m_NSEffect01))
	{
		m_NSEffect01->SetRenderCustomDepth(true);
	}
	
	// 데이터 테이블 키 맵핑
	InitPlayerData();
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
			SpawnGhostTrail();
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
	}
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//무적일 경우엔 -1.f반환
	if(m_bInvincible) 
		return -1.f;
	
	fDamage = Damage - m_Info.Armor;
	fDamage = fDamage < 1.f ? 1.f : fDamage;

	m_Info.HP -= (int32)fDamage;
	
	if (m_pHUDWidget)
		m_pHUDWidget->SetHP(m_Info.HP, m_Info.MaxHP);

	if (m_Info.HP <= 0) {
		//HandleDeath();
		fDamage = -1.f;
	}

	return fDamage;
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

void APlayerCharacter::SpawnGhostTrail()
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGhostTrail* pGhost = GetWorld()->SpawnActor<AGhostTrail>(
		AGhostTrail::StaticClass(),
		GetMesh()->GetComponentLocation(),
		GetMesh()->GetComponentRotation(), param);

	pGhost->SetMesh(m_SKMesh);
	pGhost->CopyAnimation(GetMesh());
	pGhost->SetFadeTime(0.5f);
	pGhost->SetLifeTime(0.f);
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

void APlayerCharacter::InitPlayerData()
{
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const FPlayerDataTableInfo* Info = GameInst->FindPlayerInfo(m_strDataTableKey);

		if (Info)
		{
			m_Info.Name = Info->Name;
			m_Info.Job = Info->Job;
			m_Info.Attack = Info->Attack;
			m_Info.Armor = Info->Armor;
			m_Info.MaxHP = Info->HP;
			m_Info.HP = Info->HP;
			m_Info.MaxSP = Info->SP;
			m_Info.SP = Info->SP;
			m_Info.AttackSpeed = Info->AttackSpeed;
			m_Info.MoveSpeed = Info->MoveSpeed;
			m_Info.CriticalRatio = Info->CriticalRatio;
			m_Info.CriticalDamage = Info->CriticalDamage;
			m_Info.ASkillRatio = Info->ASkillRatio;
			m_Info.SSkillRatio = Info->SSkillRatio;
			m_Info.DSkillRatio = Info->DSkillRatio;
			m_Info.FSkillRatio = Info->FSkillRatio;
			m_Info.Level = 1;
			m_Info.Exp = 0;
			m_Info.Gold = 10000;

			// 초기 속도에 속도 배율을 곱하도록 변경
			GetCharacterMovement()->MaxWalkSpeed = 600.f * Info->MoveSpeed;

			AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();

			if (GameMode)
			{
				m_pHUDWidget = GameMode->GetInGameWidget();

				if (m_pHUDWidget)
				{
					m_pHUDWidget->SetHP(m_Info.HP, m_Info.MaxHP);
					m_pHUDWidget->SetSP(m_Info.SP, m_Info.MaxSP);
				}
			}
		}
	}
}
