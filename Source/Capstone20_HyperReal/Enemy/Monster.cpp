// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../CapStoneGameInstance.h"
#include "../Manager/PlayerManager.h"
#include "MonsterAnimInstance.h"
#include "MonsterSpawnPoint.h"
#include "MonsterAIController.h"
#include "Camera/PlayerCameraManager.h"
#include "../Building/Building.h"
#include "Capstone20_HyperReal/Character/PlayerCharacter.h"
#include "../InGameModeBase.h"
#include "../UI/InGameUserWidget.h"
#include "../DamageType/AirborneDamageType.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;//기본적으로 tick은 0.5초에 한번씩 호출된다.

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetMesh()->bReceivesDecals = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	WidgetComponent->SetupAttachment(RootComponent);

	// 위젯 클래스 설정
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/MonsterHPBar.MonsterHPBar_C'"));
	if (WidgetClass.Succeeded())
	{
		WidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	WidgetComponent->SetRelativeScale3D(FVector(0.1f, 0.4f, 0.5f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	
	mSpawnPoint = nullptr;

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	mAttackEnd = false;
	bIsInvincible = false;
	bCanAttack = true;

	bIsAirborne = false;
	fAirborneTime = 0.0f;
	fMaxAirborneTime = 1.0f;
	fInitialZ = 0.0f;
}
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

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

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAirborne)
	{
		fAirborneTime += DeltaTime;
		float HalfMaxTime = fMaxAirborneTime / 2.0f;

		if (fAirborneTime <= HalfMaxTime)
		{
			// 상승
			float Alpha = fAirborneTime / HalfMaxTime;
			FVector NewLocation = GetMesh()->GetRelativeLocation();
			NewLocation.Z = fInitialZ + FMath::Lerp(0.0f, 200.0f, Alpha);  // 200.0f는 상승 높이
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
			NewLocation.Z = fInitialZ;
			GetMesh()->SetRelativeLocation(NewLocation);
			if (mAIController)
			{
				mAIController->Possess(this);
			}
		}
	}
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
		UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
		GameInst->GetPlayerManager()->GetPlayerInfo().LevelAccGold += mInfo.Gold;
		
		//돈 UI 업데이트
		AInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AInGameModeBase>();
		if(GameMode)
		{
			UInGameUserWidget* widget = GameMode->GetInGameWidget();
			if (widget)
			{
				widget->SetEarnGold(GameInst->GetPlayerManager()->GetPlayerInfo().LevelAccGold);
			}
		}
		
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

void AMonster::HandleHitAnimation(FDamageEvent const& DamageEvent)
{
	//에어본으로 변경할 수 있으면 에어본 상태로 변경
	if(bCanAirborne && !bIsAirborne && !bIsInvincible && DamageEvent.DamageTypeClass == UAirborneDamageType::StaticClass())
	{
		for(UMonsterAnimInstance* AnimInstance : AnimInstances)
		{
			if(AnimInstance)
			{
				AnimInstance->ChangeAnimType(EMonsterAnim::Airborne);
			}
		}
		StartAirborne();
	}
	else
	{
		for(UMonsterAnimInstance* AnimInstance : AnimInstances)
		{
			if(AnimInstance)
			{
				AnimInstance->ChangeAnimType(EMonsterAnim::Hit);
			}
		}
	}
}

void AMonster::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Monster Death"));
	for(UMonsterAnimInstance* AnimInstance : AnimInstances)
	{
		if(AnimInstance)
		{
			AnimInstance->ChangeAnimType(EMonsterAnim::Death);
		}
	}
	
	//monster랑 연결된 Ai를 끊음
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->UnPossess(); // 몬스터 컨트롤 해제
	}
	if(mBuilding)
	{
		mBuilding->RemoveMonster(this);
	}
	
	//무적 상태로 만들어서 대미지 더이상 안들어오게 함
	bIsInvincible = true;
}


//죽는 모션 끝난 후 notify로 호출
void AMonster::DeathEnd()
{
	//mSpawnPoint->MonsterDeath();
	Destroy();
}

void AMonster::StartAirborne()
{
	bIsAirborne = true;
	fAirborneTime = 0.0f;
	fInitialZ = GetMesh()->GetRelativeLocation().Z;
	if (GetAIController())
	{
		mAIController = GetAIController();
		GetAIController()->UnPossess();
	}
}



void AMonster::Attack()
{
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

void AMonster::SetHPBar(float fRate)
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

