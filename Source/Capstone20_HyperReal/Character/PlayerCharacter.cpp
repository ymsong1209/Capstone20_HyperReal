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
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "../Manager/PlayerManager.h"
#include "../Building/Portal.h"
#include "../Manager/RuneManager.h"
#include "../Item/Rune/Rune.h"

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

	// 스킬 쿨타입 계산 밑 UI 적용
	if (m_faccSkillACool < GetPlayerInfo().ASkillmaxcooltime * GetCoolDown())
	{
		m_faccSkillACool += DeltaTime;
		m_pHUDWidget->CalSkillCoolTime(0,  m_faccSkillACool / (GetPlayerInfo().ASkillmaxcooltime * GetCoolDown()));
	}

	if (m_faccSkillSCool < GetPlayerInfo().SSkillmaxcooltime * GetCoolDown())
	{
		m_faccSkillSCool += DeltaTime;
		m_pHUDWidget->CalSkillCoolTime(1, m_faccSkillSCool / (GetPlayerInfo().SSkillmaxcooltime * GetCoolDown()));
	}

	if (m_faccSkillDCool < GetPlayerInfo().DSkillmaxcooltime * GetCoolDown())
	{
		m_faccSkillDCool += DeltaTime;
		m_pHUDWidget->CalSkillCoolTime(2, m_faccSkillDCool / (GetPlayerInfo().DSkillmaxcooltime * GetCoolDown()));
	}

	if (m_faccSkillFCool < GetPlayerInfo().FSkillmaxcooltime * GetCoolDown())
	{
		m_faccSkillFCool += DeltaTime;
		m_pHUDWidget->CalSkillCoolTime(3, m_faccSkillFCool / (GetPlayerInfo().FSkillmaxcooltime * GetCoolDown()));
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

		pInput->BindAction(EscapeAction, ETriggerEvent::Started, this, &APlayerCharacter::TestBasecampUI);
	}
}

FPlayerInfo& APlayerCharacter::GetPlayerInfo()
{
	return Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance())->GetPlayerManager()->GetPlayerInfo();
}

int32 APlayerCharacter::GetHPMax()
{
	int32 iHPMax = GetPlayerInfo().MaxHP;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetHealthAdd();
	iHPMax *= fValue;

	return iHPMax;
}

int32 APlayerCharacter::GetSPMax()
{
	int32 iSPMax = GetPlayerInfo().MaxSP;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetSoulAdd();
	iSPMax *= fValue;

	return iSPMax;
}

int32 APlayerCharacter::GetAttack()
{
	int32 iAttack = GetPlayerInfo().Attack;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetAttackAdd();
	iAttack *= fValue;

	return iAttack;
}

int32 APlayerCharacter::GetArmor()
{
	int32 iArmor = GetPlayerInfo().Armor;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = 1.f;
	iArmor *= fValue;

	return iArmor;
}

float APlayerCharacter::GetAttackSpeed()
{
	float fAS = GetPlayerInfo().AttackSpeed;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetAttackSpeedAdd();
	fAS *= fValue;

	return fAS;
}

float APlayerCharacter::GetMoveSpeed()
{
	float fMS = GetPlayerInfo().MoveSpeed;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetMoveSpeedAdd();
	fMS *= fValue;

	return fMS;
}

float APlayerCharacter::GetCoolDown()
{
	float fCD = GetPlayerInfo().CoolDownRatio;

	// 룬 아이템 등으로 추가 계수 계산
	float fValue = GetRuneManager()->GetCoolDownAdd();
	fCD += fValue;

	return fCD;
}

URuneManager* APlayerCharacter::GetRuneManager()
{
	URuneManager* Mgr = nullptr;

	UCapStoneGameInstance* gameInst = GetWorld()->GetGameInstance<UCapStoneGameInstance>();

	if (gameInst)
		Mgr = gameInst->GetRuneManager();

	return Mgr;
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	GetRuneManager()->TakeDamageTrigger(DamageCauser, Damage);

	//무적일 경우엔 -1.f반환
	if(m_bInvincible) 
		return -1.f;

	if (GetPlayerInfo().HP > GetHPMax())
		GetPlayerInfo().HP = GetHPMax();
	
	fDamage = Damage - GetArmor();
	fDamage = fDamage < 1.f ? 1.f : fDamage;

	GetPlayerInfo().HP -= (int32)fDamage;
	
	if (m_pHUDWidget)
		m_pHUDWidget->SetHP(GetPlayerInfo().HP, GetHPMax());

	if (GetPlayerInfo().HP <= 0) {
		fDamage = -1.f;

		// 리저렉션 룬 실행
		GetRuneManager()->GetRune(ERuneType::Resurrection)->Activate();
	}

	return fDamage;
}

float APlayerCharacter::GiveDamage(AActor* _Target, float _fAttackRatio, EPlayerSkill _type)
{	
	float fResult = _Target->TakeDamage(GetAttack() * _fAttackRatio, FDamageEvent(), GetController(), this);


	UE_LOG(LogTemp, Log, TEXT("Attack : %d"), GetAttack());


	// 데미지를 받을 수 있는 오브젝트 일 때만 적용
	if (fResult != -1.f)
	{
		// 평타에 적용되는 룬 작동
		if (_type == EPlayerSkill::None)
			GetRuneManager()->NormalAttackTrigger(_Target, GetAttack() * _fAttackRatio);

		// 전체에 다 적용 되는 룬 작동
		GetRuneManager()->GiveDamageTrigger(_Target, GetAttack() * _fAttackRatio);
	}

	return fResult;
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

void APlayerCharacter::EscapeFunction()
{
	AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
	if(GameMode)
	{
		UInGameUserWidget* widget = GameMode->GetInGameWidget();
		if (widget && widget->IsVisible())
		{
			widget->CloseUI();
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
	}
	
	if(m_pPortal)
	{
		m_pPortal->TransitionToNextLevel(this);
	}
}


void APlayerCharacter::ChangeWalkSpeed(float _value)
{
	GetCharacterMovement()->MaxWalkSpeed = (m_fDefaultSpeed * _value) * GetMoveSpeed();
	GetCharacterMovement()->MaxAcceleration = (m_fDefaultAccel * _value) * GetAttackSpeed();
}

void APlayerCharacter::Heal(float fValue)
{
	GetPlayerInfo().HP += fValue;
	if(GetPlayerInfo().HP >= GetPlayerInfo().MaxHP)
		GetPlayerInfo().HP = GetPlayerInfo().MaxHP;

	m_pHUDWidget->SetHP(GetPlayerInfo().HP, GetHPMax());

	UE_LOG(LogTemp, Log, TEXT("Heal, current Hp : %d"), GetPlayerInfo().HP);
}

void APlayerCharacter::Ressurection(float fValue)
{
	GetPlayerInfo().HP = GetHPMax() * fValue;
	GetPlayerInfo().SP = GetSPMax() * fValue;

	m_pHUDWidget->SetHP(GetPlayerInfo().HP, GetHPMax());
	m_pHUDWidget->SetSP(GetPlayerInfo().SP, GetSPMax());

	// 부활 이펙트 호출
}

void APlayerCharacter::InitPlayerData()
{
	m_faccSkillACool = GetPlayerInfo().ASkillmaxcooltime;
	m_faccSkillSCool = GetPlayerInfo().SSkillmaxcooltime;
	m_faccSkillDCool = GetPlayerInfo().DSkillmaxcooltime;
	m_faccSkillFCool = GetPlayerInfo().FSkillmaxcooltime;

	ChangeWalkSpeed(1.f);

	AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();

	if (GameMode)
	{
		m_pHUDWidget = GameMode->GetInGameWidget();

		if (m_pHUDWidget)
		{
			m_pHUDWidget->SetHP(GetPlayerInfo().HP, GetPlayerInfo().MaxHP);
			m_pHUDWidget->SetSP(GetPlayerInfo().SP, GetPlayerInfo().MaxSP);
		}
	}

	//if (GameInst)
	//{
	//	const FPlayerDataTableInfo* Info = GameInst->FindPlayerInfo(m_strDataTableKey);

	//	if (Info)
	//	{
	//		m_Info.Name = Info->Name;
	//		m_Info.Job = Info->Job;
	//		m_Info.Attack = Info->Attack;
	//		m_Info.Armor = Info->Armor;
	//		m_Info.MaxHP = Info->HP;
	//		m_Info.HP = Info->HP;
	//		m_Info.MaxSP = Info->SP;
	//		m_Info.SP = Info->SP;
	//		m_Info.AttackSpeed = Info->AttackSpeed;
	//		m_Info.MoveSpeed = Info->MoveSpeed;
	//		m_Info.CriticalRatio = Info->CriticalRatio;
	//		m_Info.CriticalDamage = Info->CriticalDamage;
	//		m_Info.ASkillRatio = Info->ASkillRatio;
	//		m_Info.SSkillRatio = Info->SSkillRatio;
	//		m_Info.DSkillRatio = Info->DSkillRatio;
	//		m_Info.FSkillRatio = Info->FSkillRatio;

	//		m_Info.ASkillmaxcooltime = Info->ASkillMaxCooltime;
	//		m_Info.SSkillmaxcooltime = Info->SSkillMaxCooltime;
	//		m_Info.DSkillmaxcooltime = Info->DSkillMaxCooltime;
	//		m_Info.FSkillmaxcooltime = Info->FSkillMaxCooltime;
	//		m_faccSkillACool = m_Info.ASkillmaxcooltime;
	//		m_faccSkillSCool = m_Info.SSkillmaxcooltime;
	//		m_faccSkillDCool = m_Info.DSkillmaxcooltime;
	//		m_faccSkillFCool = m_Info.FSkillmaxcooltime;

	//		m_Info.Level = 1;
	//		m_Info.Exp = 0;
	//		m_Info.TotalGold = 10000;
	//		m_Info.LevelAccGold = 0;

	//		m_Info.AttackLevel = Info->AttackLevel;
	//		m_Info.HealthLevel = Info->HealthLevel;
	//		m_Info.SoulLevel = Info->SoulLevel;

	//		m_Info.AttackProgress = Info->AttackProgress;
	//		m_Info.HealthProgress = Info->HealthProgress;
	//		m_Info.SoulProgress = Info->SoulProgress;

	//		// 초기 속도에 속도 배율을 곱하도록 변경
	//		ChangeWalkSpeed(1.f);

	//		AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();

	//		if (GameMode)
	//		{
	//			m_pHUDWidget = GameMode->GetInGameWidget();

	//			if (m_pHUDWidget)
	//			{
	//				m_pHUDWidget->SetHP(m_Info.HP, m_Info.MaxHP);
	//				m_pHUDWidget->SetSP(m_Info.SP, m_Info.MaxSP);
	//			}
	//		}
	//	}
	//}	
}

void APlayerCharacter::TestBasecampUI()
{
	m_pHUDWidget->TestOpenTrigger();
}
