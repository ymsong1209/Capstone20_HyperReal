// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSoldier.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/DecalComponent.h"

#include "SoldierAnimInstance.h"
#include "ClickMoveController.h"
#include "LongSword.h"
#include "../Effect/EffectBase.h"
#include "../Effect/SmashCameraShake.h"
#include "../Projectile/SoldierChargeSlash.h"
#include "../Enemy/Monster.h"
#include "GhostTrail.h"
#include "../DamageType/AirborneDamageType.h"
#include "../UI/InGameUserWidget.h"
#include "../InGameModeBase.h"
#include "../Manager/RuneManager.h"
#include "../Item/Rune/Rune.h"

ASkeletonSoldier::ASkeletonSoldier() :
	m_ChargingMontage(nullptr),
	m_ChargeAttackMontage(nullptr),
	m_WhirlWindMontage(nullptr),
	m_LeapAttackMontage(nullptr),
	m_fChargingTick(0.75f),
	m_fWhilrwindDuration(4.f),
	m_fWhildWindSpeed(1000.f),
	m_fLeapMaxDistance(500.f),
	m_fChargeStartTime(0.f),
	m_iChargeAttackCount(0),
	m_fTrailCount(0.f),
	m_fTrailValue(1.f)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 86.0f);

	// 코드로 캐릭터 메쉬 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ToonSkeletonSoldier/Characters/Meshes/SKM_ToonSkeleton_Soldier_Amethyst.SKM_ToonSkeleton_Soldier_Amethyst'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		m_SKMesh = MeshAsset.Object;
	}
	GetMesh()->bReceivesDecals = false;

	// 코드로 애니메이션 블루프린트 세팅
	static ConstructorHelpers::FClassFinder<USoldierAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/A_SJWContent/Character/AB_SkeletonSoldier.AB_SkeletonSoldier_C'"));
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	// 차징 애니메이션 수동 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimCharing(TEXT("/Script/Engine.AnimMontage'/Game/A_SJWContent/Character/Animation/AM_SoldierCharging.AM_SoldierCharging'"));
	if (AnimCharing.Succeeded())
	{
		m_ChargingMontage = AnimCharing.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimChargeAttack(TEXT("/Script/Engine.AnimMontage'/Game/A_SJWContent/Character/Animation/AM_SoldierChargeAttack.AM_SoldierChargeAttack'"));
	if (AnimChargeAttack.Succeeded())
	{
		m_ChargeAttackMontage = AnimChargeAttack.Object;
	}

	// 훨윈드 애니메이션 수동 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimWhirlwind(TEXT("/Script/Engine.AnimMontage'/Game/A_SJWContent/Character/Animation/AB_SoldierWhirlwind.AB_SoldierWhirlwind'"));
	if (AnimWhirlwind.Succeeded())
	{
		m_WhirlWindMontage = AnimWhirlwind.Object;
	}

	// 리프어택 애니메이션 수동 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimLeapAttack(TEXT("/Script/Engine.AnimMontage'/Game/A_SJWContent/Character/Animation/AM_LeapAttack.AM_LeapAttack'"));
	if (AnimLeapAttack.Succeeded())
	{
		m_LeapAttackMontage = AnimLeapAttack.Object;
	}

	// 언데드 퓨리 애니메이션 수동 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimUndeadFury(TEXT("/Script/Engine.AnimMontage'/Game/A_SJWContent/Character/Animation/AM_SoldierUndeadFury.AM_SoldierUndeadFury'"));
	if (AnimUndeadFury.Succeeded())
	{
		m_UndeadFuryMontage = AnimUndeadFury.Object;
	}

	// 입력 매핑 수동 설정
	static ConstructorHelpers::FObjectFinder<UInputAction> InputA(TEXT("/Script/EnhancedInput.InputAction'/Game/A_SJWContent/Input/Action/IA_SkillA.IA_SkillA'"));
	if (InputA.Succeeded())
	{
		SkillAAction = InputA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputS(TEXT("/Script/EnhancedInput.InputAction'/Game/A_SJWContent/Input/Action/IA_SkillS.IA_SkillS'"));
	if (InputS.Succeeded())
	{
		SkillSAction = InputS.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputD(TEXT("/Script/EnhancedInput.InputAction'/Game/A_SJWContent/Input/Action/IA_SkillD.IA_SkillD'"));
	if (InputD.Succeeded())
	{
		SkillDAction = InputD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputF(TEXT("/Script/EnhancedInput.InputAction'/Game/A_SJWContent/Input/Action/IA_SkillF.IA_SkillF'"));
	if (InputF.Succeeded())
	{
		SkillFAction = InputF.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputEscape(TEXT("/Script/EnhancedInput.InputAction'/Game/A_SJWContent/Input/Action/IA_ESC.IA_ESC'"));
	if (InputEscape.Succeeded())
	{
		EscapeAction = InputEscape.Object;
	}

	// 데칼 머티리얼 로딩
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MILeapRange(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/MT_LeapAttackRange.MT_LeapAttackRange'"));
	if (MILeapRange.Succeeded())
	{
		m_pLeapAttackRangeDecalInterface = MILeapRange.Object;

		//// 리프 어택시 바닥에 생성될 범위 확인용 데칼 컴포넌트 생성
		m_pLeapAttackRangeDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("LeapRange"));
		m_pLeapAttackRangeDecal->SetDecalMaterial(m_pLeapAttackRangeDecalInterface);
		m_pLeapAttackRangeDecal->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MILeapAttack(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/MT_LeapAttack.MT_LeapAttack'"));
	if (MILeapAttack.Succeeded())
	{
		m_pLeapAttackDecalInterface = MILeapAttack.Object;
	}

	// 언데드 퓨리용 머티리얼 로딩
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MIUndeadFury(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/Material/MT_UndeadFury_Inst.MT_UndeadFury_Inst'"));
	if (MIUndeadFury.Succeeded())
	{
		m_pUndeadFuryInterface = MIUndeadFury.Object;
	}

	// 언데드 퓨리용 나이아가라 시스템 로딩
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NSUndeadFuryAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/A_SJWContent/Effect/Niagara/NS_UndeadFury.NS_UndeadFury'"));

	if (NSUndeadFuryAsset.Succeeded())
	{
		m_NSEffect01->SetAsset(NSUndeadFuryAsset.Object);
	}

	m_fAttackImpulse = 1200.f;
	m_strDataTableKey = TEXT("Soldier");
}

void ASkeletonSoldier::BeginPlay()
{
	Super::BeginPlay();

	// 디폴트 무기 액터 생성
	FName WeaponSocket(TEXT("Weapon_R"));
	m_pRWeapon = GetWorld()->SpawnActor<ALongSword>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (IsValid(m_pRWeapon))
	{
		m_pRWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		m_pRWeapon->SetActorRelativeLocation(FVector(0.f, 0.f, -30.f));
		m_pRWeapon->SetActorRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}

	if (IsValid(m_pLeapAttackRangeDecal))
	{
		m_pLeapAttackRangeDecal->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
		m_pLeapAttackRangeDecal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
		m_pLeapAttackRangeDecal->SetRelativeScale3D(FVector(0.5f, 2.6f, 2.6f));
		m_pLeapAttackRangeDecal->SetHiddenInGame(true);
	}

	m_NSEffect01->Deactivate();

	GetWorld()->GetTimerManager().SetTimer(WidgetInitializationTimerHandle, this, &ASkeletonSoldier::InitializeDynamicMaterial, 0.01f, false);
}

void ASkeletonSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (m_eUsingSkill)
	{
		// 훨윈드
	case EPlayerSkill::SkillA:
	{
		FRotator fCurRot = FRotator(0.f, 0.f, 0.f);
		SetActorRotation(fCurRot);
	}
		break;
		// 리프 어택
	case EPlayerSkill::SkillS:
	{
		if (m_bOnLeapAttackCharge)
		{
			FVector vMousePos = GetMousePosition();
			vMousePos.Z = GetActorLocation().Z;

			// 최대 거리 밖으로 이동 안하도록 설정
			if (FVector::Dist(vMousePos, GetActorLocation()) > m_fLeapMaxDistance)
			{
				FVector vDir = (vMousePos - GetActorLocation()).GetSafeNormal();
				m_vLeapAttackPos = (GetActorLocation() + vDir * m_fLeapMaxDistance);
			}
			else
				m_vLeapAttackPos = vMousePos;

			m_vLeapAttackPos.Z = GetMousePosition().Z;

			// 위치 확인용 스피어 출력
			DrawDebugSphere(GetWorld(), m_vLeapAttackPos, 10.f, 50, FColor::Green);

			if (IsValid(m_pLeapAttackDecal))
				m_pLeapAttackDecal->SetWorldLocation(m_vLeapAttackPos);
		}
	}
		break;
	case EPlayerSkill::SkillD:
		break;
	case EPlayerSkill::SkillF:
		break;
	case EPlayerSkill::None:
		break;
	default:
		break;
	}
}

void ASkeletonSoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(pInput))
	{
		// D 버튼에 차지 공격 바인딩
		pInput->BindAction(SkillDAction, ETriggerEvent::Started, this, &ASkeletonSoldier::ChargeStart);
		pInput->BindAction(SkillDAction, ETriggerEvent::Triggered, this, &ASkeletonSoldier::Charging);
		pInput->BindAction(SkillDAction, ETriggerEvent::Completed, this, &ASkeletonSoldier::ChargeAttack);

		// A 버튼에 휠윈드 공격 바인딩
		pInput->BindAction(SkillAAction, ETriggerEvent::Started, this, &ASkeletonSoldier::Whirlwind);

		// S 버틈에 도약 공격 바인딩
		pInput->BindAction(SkillSAction, ETriggerEvent::Started, this, &ASkeletonSoldier::LeapAttack);

		// F 버튼에 언데드 퓨리 바인딩
		pInput->BindAction(SkillFAction, ETriggerEvent::Started, this, &ASkeletonSoldier::UndeadFury);

		// ESC 버튼 누르면 일시정지 혹은 창 종료
		pInput->BindAction(EscapeAction, ETriggerEvent::Started, this, &ASkeletonSoldier::EscapeFunction);
	}
}

void ASkeletonSoldier::Attack()
{
	if (!m_bOnAttack && (m_eUsingSkill == EPlayerSkill::None))
	{
		// 하고 공격 모션
		if (m_arrAttackMontage.Num() == 0)
		{
			AttackEnd();
			return;
		}

		if (!m_pAnim->Montage_IsPlaying(m_arrAttackMontage[m_iAttackMontageIndex]))
		{
			// 몽타주 초기화
			m_pAnim->Montage_SetPosition(m_arrAttackMontage[m_iAttackMontageIndex], 0.f);
			m_pAnim->Montage_Play(m_arrAttackMontage[m_iAttackMontageIndex], GetAnimPlaySpeed());
		}
	}

	Super::Attack();
}

void ASkeletonSoldier::SkillEnd()
{
	switch (m_eUsingSkill)
	{
	case EPlayerSkill::SkillA:
		break;
	case EPlayerSkill::SkillS:
		m_eUsingSkill = EPlayerSkill::None;
		break;
	case EPlayerSkill::SkillD:
	{
		if (++m_iAccChargeAttackCount >= m_iChargeAttackCount)
		{
			m_pAnim->Montage_Stop(0.1f);
			m_iChargeAttackCount = 0;
			m_iAccChargeAttackCount = 0;
			m_fChargeStartTime = 0.f;
			m_eUsingSkill = EPlayerSkill::None;
		}
	}
		break;
	case EPlayerSkill::SkillF:
		m_eUsingSkill = EPlayerSkill::None;
		break;
	}
}

void ASkeletonSoldier::SpawnGhostTrail()
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

	// 색 변하는 세팅
	FVector vColor1 = FVector(0.f, 0.f, 1.f);
	FVector vColor2 = FVector(1.f, 1.f, 0.f);

	const float fTrailMaxCount = 10.f;

	m_fTrailCount += m_fTrailValue;

	if (m_fTrailCount > fTrailMaxCount)
	{
		m_fTrailCount = fTrailMaxCount;
		m_fTrailValue = -1.f;
	}
	else if (m_fTrailCount < 0.f)
	{
		m_fTrailCount = 0.f;
		m_fTrailValue = 1.f;
	}

	float fValue = (m_fTrailCount / fTrailMaxCount);
	FVector vLerpColor = FVector::SlerpNormals(vColor1, vColor2, fValue);

	pGhost->SetColorParam(vLerpColor);
}

void ASkeletonSoldier::EscapeFunction()
{
	Super::EscapeFunction();
}

void ASkeletonSoldier::ChargeStart()
{
	if (m_bOnAttack || (m_eUsingSkill != EPlayerSkill::None) || (m_faccSkillDCool < GetPlayerInfo().DSkillmaxcooltime * GetCoolDown()))
		return;

	GetCharacterMovement()->StopMovementImmediately();

	m_fChargeStartTime = GetWorld()->GetTimeSeconds();
	m_eUsingSkill = EPlayerSkill::SkillD;

	if (!m_pAnim->Montage_IsPlaying(m_ChargingMontage))
	{
		m_pAnim->Montage_SetPosition(m_ChargingMontage, 0.f);
		m_pAnim->Montage_Play(m_ChargingMontage, GetAnimPlaySpeed());
		m_iChargeAttackCount = 0;
	}

	m_pRWeapon->SwitchBlinkOverlay(true);
	m_pRWeapon->GetMIDOverlay()->SetVectorParameterValue(TEXT("Color"), FVector(1.f, 1.f, 1.f));
	m_pRWeapon->GetMIDOverlay()->SetScalarParameterValue(TEXT("BlinkSpeed"), 2.f);
}

void ASkeletonSoldier::Charging()
{
	if (m_eUsingSkill != EPlayerSkill::SkillD)
		return;

	// 마우스 방향으로 차징중 회전
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

	float fElapsedTime = GetWorld()->GetTimeSeconds() - m_fChargeStartTime;

	// 차징 카운트를 증가시켜주는 코드 포함
	if (fElapsedTime >= (m_fChargingTick * (float)(m_iChargeAttackCount + 1)))
	{
		// 오버레이 머티리얼 색상 변경
		switch (++m_iChargeAttackCount)
		{
		case 1:
			m_pRWeapon->GetMIDOverlay()->SetVectorParameterValue(TEXT("Color"), FVector(0.7f, 1.f, 0.f));
			break;
		case 2:
			m_pRWeapon->GetMIDOverlay()->SetVectorParameterValue(TEXT("Color"), FVector(0.f, 0.f, 1.f));
			break;
		}
	}

	// 차징 시간 체크하여 최대치를 넘기면 바로 공격실행
	if (fElapsedTime >= (m_fChargingTick * 3.f))
		ChargeAttack();
}

void ASkeletonSoldier::ChargeAttack()
{
	if (m_eUsingSkill != EPlayerSkill::SkillD)
		return;

	m_faccSkillDCool = 0.f;

	float fElapsedTime = GetWorld()->GetTimeSeconds() - m_fChargeStartTime;

	m_iChargeAttackCount = FMath::FloorToInt32(fElapsedTime / m_fChargingTick) + 1;

	if (!m_pAnim->Montage_IsPlaying(m_ChargeAttackMontage))
	{
		m_pAnim->Montage_SetPosition(m_ChargeAttackMontage, 0.f);
		m_pAnim->Montage_Play(m_ChargeAttackMontage, GetAnimPlaySpeed());
	}

	m_pRWeapon->SwitchBlinkOverlay(false);
}

void ASkeletonSoldier::Whirlwind()
{
	// 아무 스킬도 안쓰고 있었으면 휠윈드 실행
	if (!m_bOnAttack && (m_eUsingSkill == EPlayerSkill::None) && (m_faccSkillACool >= GetPlayerInfo().ASkillmaxcooltime * GetCoolDown()))
	{
		m_eUsingSkill = EPlayerSkill::SkillA;

		if (!m_pAnim->Montage_IsPlaying(m_WhirlWindMontage))
		{
			m_pAnim->Montage_SetPosition(m_WhirlWindMontage, 0.f);
			m_pAnim->Montage_Play(m_WhirlWindMontage, GetAnimPlaySpeed());

			// 타미어 설정해서 특정 틱마다 콜리전 발생
			GetWorldTimerManager().SetTimer(m_hAttackWhirlwindHandle, this, &ASkeletonSoldier::AttackWhirlwind, 0.5f, true, 0.f);

			// 타이머 설정해서 몇초후 훨윈드 자동 종료	
			GetWorldTimerManager().SetTimer(m_hWhirlwindHandle, this, &ASkeletonSoldier::WhirlwindEnd, GetWhirlwindMaxTime(), false);
		}

		if (m_pRWeapon)
			m_pRWeapon->StartTrail();
	}
	// 휠윈드를 쓰는 중이었으면 휠윈드 종료
	else if(m_eUsingSkill == EPlayerSkill::SkillA)
	{
		WhirlwindEnd();
	}
}

void ASkeletonSoldier::AttackWhirlwind()
{
	float fRadius = 200.f;
	float fStartPos = 50.f;
	float fEndPos = -50.f;

	FVector	Start = GetActorLocation() + GetActorUpVector() * fStartPos;
	FVector	End = GetActorLocation() + GetActorUpVector() * fEndPos;

	FCollisionQueryParams	params(NAME_None, false, this);
	TArray<FHitResult>	HitArray;

	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fRadius), params);

	if (Hit)
	{
		for (int32 i = 0; i < HitArray.Num(); ++i)
		{
			if (GiveDamage(HitArray[i].GetActor(), GetPlayerInfo().ASkillRatio, EPlayerSkill::SkillA) != -1.f)
			{
				SpawnHitEffect(HitArray[i].ImpactPoint, HitArray[i].ImpactNormal.Rotation());

				AMonster* pEnemy = Cast<AMonster>(HitArray[i].GetActor());

				if (pEnemy)
				{
				}
			}
		}
	}

#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, (fStartPos + fEndPos) / 2.f, fRadius,
		FRotationMatrix::MakeFromZ(GetActorUpVector()).ToQuat(),
		DrawColor, false, 0.5f);

#endif
}

void ASkeletonSoldier::LeapAttack()
{
	if (!m_bOnAttack && (m_eUsingSkill == EPlayerSkill::None) && (m_faccSkillSCool >= GetPlayerInfo().SSkillmaxcooltime * GetCoolDown()))
	{
		m_eUsingSkill = EPlayerSkill::SkillS;

		if (!m_pAnim->Montage_IsPlaying(m_LeapAttackMontage))
		{
			m_pAnim->Montage_SetPosition(m_LeapAttackMontage, 0.f);
			m_pAnim->Montage_Play(m_LeapAttackMontage, GetAnimPlaySpeed());
			GetCharacterMovement()->StopMovementImmediately();
			m_bOnLeapAttackCharge = true;
			m_pLeapAttackRangeDecal->SetHiddenInGame(false);

			// 낙하할 위치 알려주는 데칼 생성
			if(m_pLeapAttackDecalInterface)
				m_pLeapAttackDecal = UGameplayStatics::SpawnDecalAtLocation(this, m_pLeapAttackDecalInterface, FVector(64.f, 128.f, 128.f), 
				GetActorLocation(), FRotator(-90.f, 0.f, 0.f), 0.f);

#if ENABLE_DRAW_DEBUG
			// 거리 확인용 디버깅 오브젝트
			DrawDebugCircle(GetWorld(), GetActorLocation(), m_fLeapMaxDistance, 
				50, FColor(255.f, 255.f, 0.f), false, 1.f, 0U, 1.f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f));
#endif
		}
	}
}

void ASkeletonSoldier::AttackLeapAttack()
{
	SetActorEnableCollision(true);

	m_faccSkillSCool = 0.f;

	// Camera shake
	GetController<AClickMoveController>()->ClientStartCameraShake(USmashCameraShake::StaticClass());

	float fRadius = 100.f;
	float fStartPos = 50.f;
	float fEndPos = -50.f;

	FVector	Start = GetActorLocation() + GetActorUpVector() * fStartPos;
	FVector	End = GetActorLocation() + GetActorUpVector() * fEndPos;

	FCollisionQueryParams	params(NAME_None, false, this);
	TArray<FHitResult>	HitArray;

	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fRadius), params);

	if (Hit)
	{
		for (int32 i = 0; i < HitArray.Num(); ++i)
		{
			if (GiveDamage(HitArray[i].GetActor(), GetPlayerInfo().ASkillRatio, EPlayerSkill::SkillS) != -1.f)
			{
				SpawnHitEffect(HitArray[i].ImpactPoint, HitArray[i].ImpactNormal.Rotation());

				AMonster* pEnemy = Cast<AMonster>(HitArray[i].GetActor());

				if (pEnemy)
				{
				}
			}
		}
	}

#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, (fStartPos + fEndPos) / 2.f, fRadius,
		FRotationMatrix::MakeFromZ(GetActorUpVector()).ToQuat(),
		DrawColor, false, 0.5f);

#endif
}

void ASkeletonSoldier::UndeadFury()
{
	if (!m_bOnAttack && (m_eUsingSkill == EPlayerSkill::None) && (m_faccSkillFCool >= GetPlayerInfo().FSkillmaxcooltime * GetCoolDown()))
	{
		m_eUsingSkill = EPlayerSkill::SkillF;
		m_faccSkillFCool = 0.f;

		if (!m_pAnim->Montage_IsPlaying(m_UndeadFuryMontage))
		{
			m_pAnim->Montage_SetPosition(m_UndeadFuryMontage, 0.f);
			m_pAnim->Montage_Play(m_UndeadFuryMontage);
			GetCharacterMovement()->StopMovementImmediately();

			// 애니메이션 재생속도 변경
			SetAnimPlaySpeed(1.5f);

			// 이동 속도 변경
			ChangeWalkSpeed(1.5f);

			GetWorldTimerManager().SetTimer(m_hUndeadFuryHandle, this, &ASkeletonSoldier::UndeadFuryBuffEnd, 5.f, false);

			m_bGhostTrail = true;

			UMaterialInstanceDynamic* UndeadFuryDynamic = UMaterialInstanceDynamic::Create(m_pUndeadFuryInterface, this);

			// 오버레이 이펙트 추가
			GetMesh()->SetOverlayMaterial(UndeadFuryDynamic);

			// 파티클 활성화
			m_NSEffect01->Activate();
		}
	}
}

void ASkeletonSoldier::UndeadFuryBuffEnd()
{
	SetAnimPlaySpeed(1.f);
	ChangeWalkSpeed(1.f);

	if(GetMesh()->GetOverlayMaterial())
		GetMesh()->SetOverlayMaterial(nullptr);

	m_NSEffect01->Deactivate();
	m_bGhostTrail = false;
}

void ASkeletonSoldier::ChargeAttackEnd()
{
	m_fChargeStartTime = 0.f;
	m_eUsingSkill = EPlayerSkill::None;
}

void ASkeletonSoldier::WhirlwindEnd()
{
	m_eUsingSkill = EPlayerSkill::None;
	m_pAnim->Montage_Stop(0.f);
	GetWorldTimerManager().ClearTimer(m_hAttackWhirlwindHandle);
	GetWorldTimerManager().ClearTimer(m_hWhirlwindHandle);

	m_faccSkillACool = 0.f;

	if (m_pRWeapon)
		m_pRWeapon->EndTrail();
}

void ASkeletonSoldier::LeapAttackMove()
{
	SetActorEnableCollision(false);
	m_pLeapAttackRangeDecal->SetHiddenInGame(true);

	if (IsValid(m_pLeapAttackDecal))
	{
		m_pLeapAttackDecal->DestroyComponent();
		m_pLeapAttackDecal = nullptr;
	}

	FVector vDir = (m_vLeapAttackPos - GetActorLocation()).GetSafeNormal();
	SetActorRotation(vDir.Rotation());
	SetActorLocation(m_vLeapAttackPos);
	m_vLeapAttackPos = FVector::ZeroVector;
	m_bOnLeapAttackCharge = false;

	// Camera shake
	GetController<AClickMoveController>()->ClientStartCameraShake(USmashCameraShake::StaticClass());
}

void ASkeletonSoldier::EjectChargeSlash()
{
	FVector vLoc = GetActorLocation() + GetActorForwardVector() * 100.f;
	FTransform fTran;
	fTran.SetLocation(vLoc);
	fTran.SetRotation(GetActorRotation().Quaternion());

	ASoldierChargeSlash* pSlash = GetWorld()->SpawnActorDeferred<ASoldierChargeSlash>(ASoldierChargeSlash::StaticClass(), fTran, nullptr, nullptr, 
												ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	float fDmg = (float)GetAttack() * GetPlayerInfo().DSkillRatio;
	pSlash->SetDamage(fDmg);
	pSlash->SetOwnerController(GetController());
	UGameplayStatics::FinishSpawningActor(pSlash, fTran);
}

void ASkeletonSoldier::AttackHitCheck()
{
	switch (m_iAttackMontageIndex)
	{
	case 0:
	case 1:
		AttackCrossCut();
		break;
	case 2:
		AttackUpperCut();
		break;
	case 3:
		AttackSmashCut();
		break;
	}
}


void ASkeletonSoldier::AttackCrossCut()
{
	float fDegree = 120.f;
	TMap<AActor*, FHitResult> HitResultMap;
	FCollisionQueryParams	params(NAME_None, false, this);

	int32 iCount = 7;
	float fRadius = 30.f;
	float fStartPos = 50.f;
	float fEndPos = 150.f;

	for (int i = 0; i < iCount; i++)
	{
		FVector vDir = GetActorForwardVector();
		FRotator vRot = FRotator(0.f, ((fDegree / -2.f) + (fDegree / iCount * i)), 0.f);

		FQuat QuatRot = FQuat(vRot);
		vDir = QuatRot.RotateVector(vDir);

		FVector	Start = GetActorLocation() + vDir * fStartPos;
		FVector	End = GetActorLocation() + vDir * fEndPos;

		TArray<FHitResult>	HitArray;
		bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel4,
			FCollisionShape::MakeSphere(fRadius), params);

		if (Hit)
		{
			for (int32 j = 0; j < HitArray.Num(); ++j)
			{
				HitResultMap.Add(HitArray[j].GetActor(), HitArray[j]);
			}
		}

#if ENABLE_DRAW_DEBUG

		FColor	DrawColor = Hit ? FColor::Red : FColor::Green;

		DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, (fStartPos + fEndPos) / 2.f, fRadius,
			FRotationMatrix::MakeFromZ(vDir).ToQuat(),
			DrawColor, false, 0.5f);

#endif
	}

	// 중복 충돌을 제거하고 hit 으 정보를 활용하기 위해 map 으로 변경
	for (const auto& Hit : HitResultMap)
	{
		SpawnHitEffect(Hit.Value.ImpactPoint, Hit.Value.ImpactNormal.Rotation());
		
		if (GiveDamage(Hit.Key, 1.f, EPlayerSkill::None) != -1.f)
		{
			//AMonster* pEnemy = Cast<AMonster>(HitArray[i].GetActor());

			//if (pEnemy)
			//{
			//}
		}
	}
}

void ASkeletonSoldier::AttackUpperCut()
{
	float fRadius = 70.f;
	float fStartPos = 50.f;
	float fEndPos = 200.f;

	FVector	Start = GetActorLocation() + GetActorForwardVector() * fStartPos;
	FVector	End = GetActorLocation() + GetActorForwardVector() * fEndPos;

	FCollisionQueryParams	params(NAME_None, false, this);
	TArray<FHitResult>	HitArray;
	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fRadius), params);

	if (Hit)
	{
		for (int32 i = 0; i < HitArray.Num(); ++i)
		{
			SpawnHitEffect(HitArray[i].ImpactPoint, HitArray[i].ImpactNormal.Rotation());

			if (GiveDamage(HitArray[i].GetActor(), 1.f, EPlayerSkill::None) != -1.f)
			{
				// 공중으로 뛰울 수 있으면 뛰우도록 해야함
				//AMonster* pEnemy = Cast<AMonster>(HitArray[i].GetActor());

				//if (pEnemy)
				//{
				//}
			}
		}
	}

#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, (fStartPos + fEndPos) / 2.f, fRadius,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);

#endif
}

void ASkeletonSoldier::AttackSmashCut()
{
	// Camera shake
	GetController<AClickMoveController>()->ClientStartCameraShake(USmashCameraShake::StaticClass());

	float fRadius = 70.f;
	float fStartPos = 50.f;
	float fEndPos = 200.f;

	FVector	Start = GetActorLocation() + GetActorForwardVector() * fStartPos;
	FVector	End = GetActorLocation() + GetActorForwardVector() * fEndPos;

	FCollisionQueryParams	params(NAME_None, false, this);
	TArray<FHitResult>	HitArray;
	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fRadius), params);

	if (Hit)
	{
		for (int32 i = 0; i < HitArray.Num(); ++i)
		{
			SpawnHitEffect(HitArray[i].ImpactPoint, HitArray[i].ImpactNormal.Rotation());

			// 에어본 대미지 타입 사용
			UAirborneDamageType* AirborneDamageType = NewObject<UAirborneDamageType>();
			FDamageEvent DamageEvent;
			DamageEvent.DamageTypeClass = UAirborneDamageType::StaticClass();
			
			if (GiveDamage(HitArray[i].GetActor(), 1.2f, EPlayerSkill::None) != -1.f)
			{
				// 몬스터라면 약간 앞으로 밀쳐내기
				AMonster* pEnemy = Cast<AMonster>(HitArray[i].GetActor());

				if (pEnemy)
				{
					FVector vCurPos = GetActorLocation();
					FVector vEnemyPos = pEnemy->GetActorLocation();

					FVector vDir = (vEnemyPos - vCurPos).GetSafeNormal();
					pEnemy->GetCharacterMovement()->AddImpulse(vDir * 1000.f, true);
				}
			}
		}
	}

#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Hit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, (fStartPos + fEndPos) / 2.f, fRadius,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);

#endif
}

void ASkeletonSoldier::SpawnHitEffect(FVector _vLoc, FRotator _vRot)
{
	FActorSpawnParameters param;

	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(_vLoc, _vRot, param);

	Effect->SetNiagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Impacts/NS_Demon_Slash_Impact.NS_Demon_Slash_Impact'"));
}

void ASkeletonSoldier::InitializeDynamicMaterial()
{
	// UI 설정
	if (m_pHUDWidget)
	{
		UTexture2D* SkillAIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon4.icon4'")));

		if (SkillAIcon)
		{
			m_pHUDWidget->SetSkillImage(0, SkillAIcon);
			m_pHUDWidget->SetSkillBackImage(0, SkillAIcon);
		}

		UTexture2D* SkillSIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon1.icon1'")));
		if (SkillSIcon)
		{
			m_pHUDWidget->SetSkillImage(1, SkillSIcon);
			m_pHUDWidget->SetSkillBackImage(1, SkillSIcon);
		}

		UTexture2D* SkillDIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon2.icon2'")));
		if (SkillDIcon)
		{
			m_pHUDWidget->SetSkillImage(2, SkillDIcon);
			m_pHUDWidget->SetSkillBackImage(2, SkillDIcon);
		}

		UTexture2D* SkillFIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/A_KHIContent/UI/Image/icon3.icon3'")));
		if (SkillFIcon)
		{
			m_pHUDWidget->SetSkillImage(3, SkillFIcon);
			m_pHUDWidget->SetSkillBackImage(3, SkillFIcon);
		}
	}
}

float ASkeletonSoldier::GetWhirlwindMaxTime()
{
	float fResult = m_fWhilrwindDuration;

	URuneManager* RuneMgr = GetRuneManager();
	fResult += RuneMgr->GetRune(ERuneType::Rotation)->GetExtraValue();
	return fResult;
}
