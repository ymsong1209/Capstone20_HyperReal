// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "../Enemy/Monster.h"
#include "../CapStoneGameInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Character/PlayerCharacter.h"
#include "../Manager/RuneManager.h"
#include "../Item/Rune/DemolitionRune.h"

// Sets default values
ABuilding::ABuilding() :
	mCurPhase(0),
	mAccTime(0.f),
	mTotalTime(0.f),
	mbIsActivated(false),
	mbIsInvincible(false),
	mbIsShaking(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	mHitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitParticle"));
	RootComponent = mMesh;
	// 생성자에서 첫 번째 메쉬로 초기화
	if (mMeshes.Num() > 0)
	{
		mMesh->SetStaticMesh(mMeshes[0]);
	}
	
	//mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->SetCollisionProfileName(TEXT("Building"));
	mMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mMesh->bReceivesDecals = false;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DestroyRate"));
	WidgetComponent->SetupAttachment(RootComponent);

	// 위젯 클래스 설정
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_KHIContent/UI/DestroyRate.DestroyRate_C'"));
	if (WidgetClass.Succeeded())
	{
		WidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	//WidgetComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	WidgetComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	SetCanBeDamaged(true);
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst) {
		const FBuildingDataTableInfo* Info = GameInst->FindBuildingInfo(mDataTableKey);
		if (Info) {
			mInfo.Name = Info->Name;
			mInfo.Attack = Info->Attack;
			mInfo.Armor = Info->Armor;
			mInfo.HP = Info->HP;
			mInfo.MaxHP = Info->HP;
			mInfo.MP = Info->MP;
			mInfo.MaxMP = Info->MP;
			mInfo.AttackSpeed = Info->AttackSpeed;
			mInfo.SpawnIntervalSeconds = Info->SpawnIntervalSeconds;
			mInfo.MonstersPerSpawn = Info->MonstersPerSpawn;
			mInfo.SpawnRadius = Info->SpawnRadius;
			mInfo.Level = Info->Level;
			mInfo.Exp = Info->Exp;
			mInfo.Gold = Info->Gold;
			mInfo.PhaseTriggerHP = Info->PhaseTriggerHP;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("No Info"));
		}
	}
	SetDestroyRateText(100);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(mbIsActivated == false) return;
	
	mAccTime += DeltaTime;
	mTotalTime += DeltaTime;

	if(mAccTime >= mInfo.SpawnIntervalSeconds)
	{
		mAccTime = 0.f;
		SpawnMonster();
	}

}

void ABuilding::Activate()
{
	mbIsActivated = true;
	SpawnMonster();
	
}

void ABuilding::SpawnMonster()
{
	for(int i = 0;i<mInfo.MonstersPerSpawn;++i)
	{
		FVector2D RandCircle = FMath::RandPointInCircle(mInfo.SpawnRadius);
		FVector SpawnLocation = GetActorLocation() + FVector(RandCircle.X, RandCircle.Y, 0); // 2D 포인트를 3D 벡터로 변환
		FRotator SpawnRotation = GetActorRotation();

		// 땅에 스폰되도록 높이를 조정
		FVector Start = SpawnLocation + FVector(0, 0, 1000);  // 공중에서 시작
		FVector End = SpawnLocation - FVector(0, 0, 1000);    // 지면 방향으로 레이캐스트

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);  // 건물은 무시
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

		if (bHit)
		{
			// 레이캐스트에 성공하면 지면에 스폰
			SpawnLocation = HitResult.Location;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 배열에서 랜덤하게 몬스터 클래스 선택
		if(mMonsterClasses.Num()< 1) return;
		TSubclassOf<AMonster> ChosenMonsterClass = mMonsterClasses[FMath::RandRange(0, mMonsterClasses.Num() - 1)];
		AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>(ChosenMonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		if (IsValid(SpawnedMonster))
		{
			//생성된 몬스터에게 building알려줌
			SpawnedMonster->SetOwnerBuilding(this);
			mMonsterVector.Add(SpawnedMonster);
		}
	}
}


void ABuilding::RemoveMonster(AMonster* monster)
{
	if (monster)
	{
		mMonsterVector.RemoveSingle(monster);  // 몬스터 제거
	}
}


float ABuilding::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                            AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//무적 상태인 경우
	if (mbIsInvincible || Damage == -1.f)
		return Damage;

	//비활성화되어있었으면 활성화시킴
	if(mbIsActivated == false)
	{
		Activate();
	}
	
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	URuneManager* RuneManager = GameInst->GetRuneManager();
	UDemolitionRune* DemolitionRune = Cast<UDemolitionRune>(RuneManager->GetRune(ERuneType::Demolition));
	if(DemolitionRune)
	{
		//파괴의 룬이 있을 경우, 건물에 추가 대미지
		Damage *= DemolitionRune->GetExtraValue();
	}
	
	Damage -= mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;

	if (mInfo.HP <= 0) {
		//Todo : Chaos Crush적용
		HandleDeath();
		//죽었을 경우 -1.f반환
		Damage = -1.f;
	}
	SpawnHitParticles();
	HitShake();

	int rate = static_cast<int>(static_cast<float>(mInfo.HP) * 100 / static_cast<float>(mInfo.MaxHP));
	SetDestroyRateText(rate);
	return Damage;
}

//건물 죽음처리
void ABuilding::HandleDeath()
{
	mbIsInvincible = true;
	//KillAllMonsters();
	Destroy();
}

void ABuilding::SpawnHitParticles() const
{
	int SpawnCount = FMath::RandRange(5, 10);

	for (int i = 0; i < SpawnCount; ++i)
	{
		// 메쉬의 바운딩 박스 중심 및 크기를 가져옴
		FVector Origin = mMesh->GetComponentLocation();
		FVector BoxExtent = mMesh->Bounds.BoxExtent;

		// 메쉬 콜라이더의 바깥 표면 근처에 랜덤한 위치 생성
		FVector RandomDirection = FMath::VRand();
		RandomDirection.Z = FMath::Abs(RandomDirection.Z); // Z 방향은 항상 위쪽
		RandomDirection.Normalize();

		// 콜라이더 외벽을 향한 랜덤 위치를 박스 범위 안에서 계산
		FVector GuessLocation = Origin + (RandomDirection * BoxExtent) * FMath::RandRange(1.0f, 1.2f);
	
		// 메쉬의 콜라이더 표면에 가장 가까운 위치를 찾음
		FVector ClosestPointOnSurface;
		if (mMesh->GetClosestPointOnCollision(GuessLocation, ClosestPointOnSurface))
		{
			if (mHitParticle)
			{
				//UE_LOG(LogTemp, Error, TEXT("Particles spawned at %s"), *ClosestPointOnSurface.ToString());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mHitParticle->Template, ClosestPointOnSurface, FRotator::ZeroRotator, true);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No Particles"));
			}

			// 디버그 용도로 파티클 스폰 위치를 시각화
			//DrawDebugSphere(GetWorld(), ClosestPointOnSurface, 20.0f, 12, FColor::Red, false, 2.0f);
		
		}
		else
		{
			//UE_LOG(LogTemp, Error, TEXT("Could not find closest point on surface"));
		}
	}
	
	
}
void ABuilding::HitShake()
{
	if (!mbIsShaking)
	{
		mbIsShaking = true; // 흔들림 시작 표시
		mOriginalLocation = GetActorLocation(); // 원래 위치 저장

		float ShakeAmount = 10.0f;
		FVector NewLocation = mOriginalLocation + FMath::VRand() * ShakeAmount;
		SetActorLocation(NewLocation);

		FTimerHandle ShakeTimerHandle;
		// 원래 위치로 돌아가는 로직
		GetWorld()->GetTimerManager().SetTimer(ShakeTimerHandle, [this]() {
			SetActorLocation(mOriginalLocation);
			mbIsShaking = false; // 흔들림 종료 표시
		}, 0.1f, false);
	}
}

void ABuilding::KillAllMonsters()
{
	for (int i = mMonsterVector.Num() - 1; i >= 0; --i)
	{
		AMonster* monster = mMonsterVector[i];
		if (monster)
		{
			monster->HandleDeath();
		}
	}
}


void ABuilding::Attack()
{
}

void ABuilding::SetDestroyRateText(int iRate)
{
	UUserWidget* UserWidget = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if (UserWidget)
	{
		// MonsterHPProgressBar 이름의 ProgressBar 찾기
		UTextBlock* destroyRateTextBlock = Cast<UTextBlock>(UserWidget->GetWidgetFromName(TEXT("DestroyRate")));
		if (destroyRateTextBlock)
		{
			FString str = FString::FromInt(iRate);
			str += "%";
			destroyRateTextBlock->SetText(FText::FromString(str));
		}
	}

	
}
