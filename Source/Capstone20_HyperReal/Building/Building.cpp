// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "../Enemy/Monster.h"
#include "../CapStoneGameInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Character/PlayerCharacter.h"

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
	
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	mMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mMesh->bReceivesDecals = false;
	
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
	UE_LOG(LogTemp, Display, TEXT("SpawnMonsterCalled"));
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
		TSubclassOf<AMonster> ChosenMonsterClass = mMonsterClasses[FMath::RandRange(0, mMonsterClasses.Num() - 1)];
		AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>(ChosenMonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		if (SpawnedMonster)
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

	Damage = DamageAmount - mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;

	if (mInfo.HP <= 0) {
		//Todo : Chaos Crush적용
		Death();
		//죽었을 경우 -1.f반환
		Damage = -1.f;
	}
	//SpawnHitParticles();
	return Damage;
}

//건물 죽음처리
void ABuilding::Death()
{
	mbIsInvincible = true;
	KillAllMonsters();
	Destroy();
}

void ABuilding::SpawnHitParticles() const
{
	
	int SpawnCount = FMath::RandRange(2, 5);

	// 건물의 Bounding Box 크기를 구함
	FBox Bounds = GetComponentsBoundingBox(true);
	FVector Min = Bounds.Min;
	FVector Max = Bounds.Max;

	for (int i = 0; i < SpawnCount; ++i)
	{
		// 건물 경계 부근에서 파티클이 나타나도록 위치를 랜덤으로 결정
		FVector SpawnLocation = FVector(
			FMath::RandRange(Min.X, Max.X),   
			FMath::RandRange(Min.Y, Max.Y),   
			FMath::RandRange(Min.Z, Max.Z)    
		);

		// 파티클 시스템 스폰
		if(mHitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mHitParticle->Template, SpawnLocation, FRotator::ZeroRotator, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Particles"));
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