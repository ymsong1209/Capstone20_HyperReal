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
	// �����ڿ��� ù ��° �޽��� �ʱ�ȭ
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
		FVector SpawnLocation = GetActorLocation() + FVector(RandCircle.X, RandCircle.Y, 0); // 2D ����Ʈ�� 3D ���ͷ� ��ȯ
		FRotator SpawnRotation = GetActorRotation();

		// ���� �����ǵ��� ���̸� ����
		FVector Start = SpawnLocation + FVector(0, 0, 1000);  // ���߿��� ����
		FVector End = SpawnLocation - FVector(0, 0, 1000);    // ���� �������� ����ĳ��Ʈ

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);  // �ǹ��� ����
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

		if (bHit)
		{
			// ����ĳ��Ʈ�� �����ϸ� ���鿡 ����
			SpawnLocation = HitResult.Location;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// �迭���� �����ϰ� ���� Ŭ���� ����
		TSubclassOf<AMonster> ChosenMonsterClass = mMonsterClasses[FMath::RandRange(0, mMonsterClasses.Num() - 1)];
		AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>(ChosenMonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		if (SpawnedMonster)
		{
			//������ ���Ϳ��� building�˷���
			SpawnedMonster->SetOwnerBuilding(this);
			mMonsterVector.Add(SpawnedMonster);
		}
	}
}


void ABuilding::RemoveMonster(AMonster* monster)
{
	if (monster)
	{
		mMonsterVector.RemoveSingle(monster);  // ���� ����
	}
}


float ABuilding::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                            AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//���� ������ ���
	if (mbIsInvincible)
		return Damage;

	//��Ȱ��ȭ�Ǿ��־����� Ȱ��ȭ��Ŵ
	if(mbActivated == false)
	{
		Activate();
	}

	Damage = DamageAmount - mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;

	if (mInfo.HP <= 0) {
		//Todo : Chaos Crush����
		Death();
		Damage = -1.f;
	}
	
	return Damage;
}

//�ǹ� ����ó��
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