// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Monster.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMonsterInfo mInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;
	class UMonsterAnimInstance* mAnim;
	class AMonsterAIController* mAIController;
	class AMonsterSpawnPoint* mSpawnPoint;

	class ABuilding* mBuilding;

	FString mDataTableKey;

	bool mAttackEnd;
	bool bIsInvincible;
	bool bCanAttack;

	bool  bIsAirborne;
	float fAirborneTime;
	float fMaxAirborneTime;
	float fInitialZ;
public:
	bool GetAttackEnd() const { return mAttackEnd; }
	class UMonsterAnimInstance* GetAnimInstance() const { return mAnim; }
	const FMonsterInfo& GetMonsterInfo() const { return mInfo; }
	void SetSpawnPoint(class AMonsterSpawnPoint* Point) { mSpawnPoint = Point; }
	void SetOwnerBuilding(class ABuilding* Building) { mBuilding = Building; }
	ABuilding* GetOwnerBuilding() { return mBuilding; }
	void SetAttackEnd(bool End) { mAttackEnd = End; }

	void SetCanAttack(bool _attack){bCanAttack = _attack;}
	bool GetCanAttack(){return bCanAttack;}
	void SetHPBar(float fRate);

	AMonsterAIController* GetAIController() const {return mAIController;}
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void HandleDeath();
	void DeathEnd();
	void StartAirborne();

public:
	virtual void Attack();
};
