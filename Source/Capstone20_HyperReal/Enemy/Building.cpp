// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Monster.h"
#include "../CapStoneGameInstance.h"
#include "../Character/PlayerCharacter.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
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

	mCurPhase = 0;
	mTotalTime = 0.f;
	mAccTime = 0.f;
	mbIsInvincible = false;
	mbActivated = false;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	mDataTableKey = "TowerA";
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
	if(mbActivated == false) return;
	
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
	mbActivated = true;
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
	if (mbIsInvincible)
		return Damage;

	//비활성화되어있었으면 활성화시킴
	if(mbActivated == false)
	{
		Activate();
	}

	Damage = DamageAmount - mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;

	if (mInfo.HP <= 0) {
		//Todo : Chaos Crush적용
		Death();
		Damage = -1.f;
	}
	
	return Damage;
}

//건물 죽음처리
void ABuilding::Death()
{
	mbIsInvincible = true;
	KillAllMonsters();
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