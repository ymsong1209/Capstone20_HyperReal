// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../CapStoneGameInstance.h"
#include "../Manager/PlayerManager.h"
#include "MonsterAnimInstance.h"
#include "MonsterSpawnPoint.h"
#include "MonsterAIController.h"
#include "Camera/PlayerCameraManager.h"
#include "../Building/Building.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../DamageType/AirborneDamageType.h"
#include "../Manager/LevelManager.h"

AMonster::AMonster()
	: mSpawnPoint(nullptr)
	, mBuilding(nullptr)
	, bCanAttack(true)
	, fAirborneStartZ(0.f)
	, mAttackEnd(true)
	, bIsInvincible(false)
	, bCanAirborne(true)
	, bIsAirborne(false)
	, fAirborneTime(0.f)
	, fMaxAirborneTime(1.f)	
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetMesh()->bReceivesDecals = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	WidgetComponent->SetRelativeScale3D(FVector(0.1f, 0.4f, 0.5f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	// 위젯 클래스 설정
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/MonsterHPBar.MonsterHPBar_C'"));
	if (WidgetClass.Succeeded())
	{
		WidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleAirborne(DeltaTime);
}

//-1.f return시 몬스터 사망
float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//무적 상태인 경우
	if (bIsInvincible || Damage == -1.f)
		return Damage;

	Damage = DamageAmount - mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;
	HandleHitAnimation(DamageEvent);

	if (mInfo.HP <= 0) {
		//player에게 몬스터의 돈을 줌
		UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());;
		AddGoldToPlayer(GameInst);
		AddGoldToUI(GameInst);

		ULevelManager* LevelManager = GameInst->GetLevelManager();
		LevelManager->AddMonsterDeathCount();

		HandleDeath();
		//죽었을 경우 -1.f반환
		Damage = 0.f;
	}

	//플레이어가 몬스터의 인식 범위 밖에서 때릴 경우, 플레이어 추적해야함
	// if (AAIController* AIController = Cast<AAIController>(Controller)) {
	// 	if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent()) {
	// 		BlackboardComp->SetValueAsObject(TEXT("Target"), DamageCauser);
	// 	}
	// }
	SetActorTickInterval(0.f);

	float rate = static_cast<float>(mInfo.HP) / static_cast<float>(mInfo.MaxHP);
	SetHPBar(rate);
	return Damage;
}

void AMonster::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Monster Death"));
	for (UMonsterAnimInstance* AnimInstance : AnimInstances)
	{
		if (AnimInstance)
		{
			AnimInstance->ChangeAnimType(EMonsterAnim::Death);
		}
	}

	//monster랑 연결된 Ai를 끊음
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->UnPossess(); // 몬스터 컨트롤 해제
	}
	if (mBuilding)
	{
		mBuilding->RemoveMonster(this);
	}

	//무적 상태로 만들어서 대미지 더이상 안들어오게 함
	bIsInvincible = true;
}


void AMonster::DeathEnd()
{
	AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
	if (GameMode)
	{
		GameMode->ReturnMonsterToPool(this);
	}
}

void AMonster::OnPoolMonsterSpawned()
{
	SetMonsterInfo();
	SetHPBar(1.f);
	bIsInvincible = false;
	bCanAttack = true;
	bIsAirborne = false;
	fAirborneTime = 0.0f;
	fAirborneStartZ = 0.0f;
	SetActorTickInterval(0.5f);
	for(UMonsterAnimInstance* AnimInstance : AnimInstances)
	{
		if(AnimInstance)
		{
			AnimInstance->ChangeAnimType(EMonsterAnim::Idle);
		}
	}
	
	if (!mAIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AIController found. Spawning a new one for %s"), *GetName());
        
		mAIController = GetWorld()->SpawnActor<AMonsterAIController>(AMonsterAIController::StaticClass());
		if (mAIController)
		{
			mAIController->Possess(this);
			UE_LOG(LogTemp, Warning, TEXT("AIController successfully possessed: %s"), *GetName());
		}
	}
	else
	{
		mAIController->Possess(this);
	}
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	SetMonsterInfo();
}


void AMonster::SetMonsterInfo()
{
	mAIController = Cast<AMonsterAIController>(GetController());

	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst) {
		const FMonsterDataTableInfo* Info = GameInst->FindMonsterInfo(mDataTableKey);
		if (Info) {
			mInfo.Name = Info->Name;
			mInfo.Attack = Info->Attack;
			mInfo.Armor = Info->Armor;
			mInfo.HP = Info->HP;
			mInfo.MaxHP = Info->HP;
			mInfo.MP = Info->MP;
			mInfo.MaxMP = Info->MP;
			mInfo.AttackSpeed = Info->AttackSpeed;
			mInfo.MoveSpeed = Info->MoveSpeed;
			mInfo.CriticalRatio = Info->CriticalRatio;
			mInfo.CriticalDamage = Info->CriticalDamage;
			mInfo.TraceDistance = Info->TraceDistance;
			mInfo.AttackDistance = Info->AttackDistance;
			mInfo.Level = Info->Level;
			mInfo.Exp = Info->Exp;
			mInfo.Gold = Info->Gold;

			GetCharacterMovement()->MaxWalkSpeed = Info->MoveSpeed;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("No Info"));
		}
	}
}

void AMonster::HandleHitAnimation(FDamageEvent const& DamageEvent)
{
	//에어본으로 변경할 수 있으면 에어본 상태로 변경
	if (bCanAirborne && !bIsAirborne && !bIsInvincible && DamageEvent.DamageTypeClass == UAirborneDamageType::StaticClass())
	{
		for (UMonsterAnimInstance* AnimInstance : AnimInstances)
		{
			if (AnimInstance)
			{
				AnimInstance->ChangeAnimType(EMonsterAnim::Airborne);
			}
		}
		StartAirborne();
	}
	else
	{
		for (UMonsterAnimInstance* AnimInstance : AnimInstances)
		{
			if (AnimInstance)
			{
				AnimInstance->ChangeAnimType(EMonsterAnim::Hit);
			}
		}
	}
}

void AMonster::StartAirborne()
{
	bIsAirborne = true;
	fAirborneTime = 0.0f;
	fAirborneStartZ = GetMesh()->GetRelativeLocation().Z;
	if (mAIController)
	{
		mAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}


void AMonster::SetAnimation(EMonsterAnim AnimType)
{
	for(UMonsterAnimInstance* AnimInstance : AnimInstances)
	{
		if(AnimInstance)
		{
			AnimInstance->ChangeAnimType(AnimType);
		}
	}
}

void AMonster::SetHPBar(const float fRate)
{

	UUserWidget* UserWidget = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if (UserWidget)
	{
		// MonsterHPProgressBar 이름의 ProgressBar 찾기
		UProgressBar* MonsterHPProgressBar = Cast<UProgressBar>(UserWidget->GetWidgetFromName(TEXT("MonsterHPProgressBar")));
		if (MonsterHPProgressBar)
		{
			// 프로그래스바와 상호작용 (예: 값 설정, 스타일 변경 등)
			MonsterHPProgressBar->SetPercent(fRate); // 체력을 75%로 설정
			// 추가적인 로직 수행
		}
	}
}

void AMonster::HandleAirborne(float DeltaTime)
{
	if (bIsAirborne)
	{
		fAirborneTime += DeltaTime;
		float HalfMaxTime = fMaxAirborneTime / 2.0f;

		if (fAirborneTime <= HalfMaxTime)
		{
			// 상승
			float Alpha = fAirborneTime / HalfMaxTime;
			FVector NewLocation = GetMesh()->GetRelativeLocation();
			NewLocation.Z = fAirborneStartZ + FMath::Lerp(0.0f, 200.0f, Alpha);  // 200.0f는 상승 높이
			GetMesh()->SetRelativeLocation(NewLocation);
		}
		else if (fAirborneTime <= fMaxAirborneTime)
		{
			// 하강
			float Alpha = (fAirborneTime - HalfMaxTime) / HalfMaxTime;
			FVector NewLocation = GetMesh()->GetRelativeLocation();
			NewLocation.Z = fAirborneTime + FMath::Lerp(200.0f, 0.0f, Alpha);  // 200.0f는 상승 높이
			GetMesh()->SetRelativeLocation(NewLocation);
		}
		else
		{
			// 에어본 상태 종료
			bIsAirborne = false;
			fAirborneTime = 0.0f;
			FVector NewLocation = GetMesh()->GetRelativeLocation();
			NewLocation.Z = fAirborneStartZ;
			GetMesh()->SetRelativeLocation(NewLocation);
			if (mAIController)
			{
				ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				mAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), Player);
			}
		}
	}
}

void AMonster::AddGoldToPlayer(UCapStoneGameInstance* GameInst) const
{
	GameInst->GetPlayerManager()->GetPlayerInfo().LevelAccGold += mInfo.Gold;
}

void AMonster::AddGoldToUI(UCapStoneGameInstance* GameInst) const
{
	if (const AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>())
	{
		if (UInGameUserWidget* Widget = GameMode->GetInGameWidget())
		{
			Widget->SetEarnGold(GameInst->GetPlayerManager()->GetPlayerInfo().LevelAccGold);
		}
	}
}