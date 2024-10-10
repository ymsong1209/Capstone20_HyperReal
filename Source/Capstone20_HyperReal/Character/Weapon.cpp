// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()	:
	m_ASWeapon(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	SetRootComponent(m_Capsule);

	m_WeaponMesh->SetupAttachment(m_Capsule);
	m_Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MIBlinkOverlay(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/A_SJWContent/Effect/Material/MT_BlinkFresnel_inst.MT_BlinkFresnel_inst'"));
	if (MIBlinkOverlay.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Blink Overlay Load Succeed"));
		m_pBlinkOverlayInterface = MIBlinkOverlay.Object;
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ESP 효과용 커스텀 뎁스 패스 활성화 코드
	m_WeaponMesh->SetRenderCustomDepth(true);
	m_WeaponMesh->CustomDepthStencilValue = 100;

	m_MIDBlinkOverlay = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), m_pBlinkOverlayInterface);
	if (m_MIDBlinkOverlay)
		UE_LOG(LogTemp, Log, TEXT("Make Blink Overlay Dynamic Material Succeed"));
}

void AWeapon::SwitchBlinkOverlay(bool _bSwitch)
{
	if (_bSwitch)
		m_WeaponMesh->SetOverlayMaterial(m_MIDBlinkOverlay);
	else
		m_WeaponMesh->SetOverlayMaterial(nullptr);
}

void AWeapon::StartTrail()
{
	if(m_ASWeapon)
		m_WeaponMesh->PlayAnimation(m_ASWeapon, true);
}

void AWeapon::EndTrail()
{
	if (m_ASWeapon)
		m_WeaponMesh->SetAnimation(nullptr);
}


