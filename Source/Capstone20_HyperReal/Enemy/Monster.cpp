// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../CapStoneGameInstance.h"

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

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	UCapStoneGameInstance* GameInst = Cast<UCapStoneGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst) {
		const FMonsterDataTableInfo* Info = GameInst->FindMonsterInfo(mDataTableKey);
		if (Info) {
			UE_LOG(LogTemp, Display, TEXT("Info"));
			m_Info.Name = Info->Name;
			m_Info.Attack = Info->Attack;
			m_Info.Armor = Info->Armor;
			m_Info.HP = Info->HP;
			m_Info.MaxHP = Info->HP;
			m_Info.MP = Info->MP;
			m_Info.MaxMP = Info->MP;
			m_Info.AttackSpeed = Info->AttackSpeed;
			m_Info.MoveSpeed = Info->MoveSpeed;
			m_Info.CriticalRatio = Info->CriticalRatio;
			m_Info.CriticalDamage = Info->CriticalDamage;
			m_Info.TraceDistance = Info->TraceDistance;
			m_Info.AttackDistance = Info->AttackDistance;
			m_Info.Level = Info->Level;
			m_Info.Exp = Info->Exp;
			m_Info.Gold = Info->Gold;
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

float AMonster::TakeDamage(float _Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(_Damage, DamageEvent, EventInstigator, DamageCauser);
	return Damage;
}
