// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../CapStoneGameInstance.h"
#include "MonsterAnimInstance.h"
#include "MonsterSpawnPoint.h"
#include "MonsterAIController.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetMesh()->bReceivesDecals = false;

	SetCanBeDamaged(true);

	mSpawnPoint = nullptr;

	AIControllerClass = AMonsterAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	mAttackEnd = false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	mAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst) {
		const FMonsterDataTableInfo* Info = GameInst->FindMonsterInfo(mDataTableKey);
		if (Info) {
			UE_LOG(LogTemp, Display, TEXT("Info"));
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
}

//-1.f return시 몬스터 사망
float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//무적 상태인 경우
	if (DamageAmount == 0.f)
		return Damage;

	Damage = DamageAmount - mInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	mInfo.HP -= (int32)Damage;

	if (mInfo.HP <= 0) {
		mAnim->ChangeAnimType(EMonsterAnim::Death);
		Damage = -1.f;
	}

	UE_LOG(LogTemp, Display, TEXT("Damage : %.2f"), DamageAmount);
	
	return Damage;
}

//죽는 모션 끝난 후 호출
void AMonster::Death()
{
	mSpawnPoint->MonsterDeath();
	Destroy();
}

void AMonster::Attack()
{
}
