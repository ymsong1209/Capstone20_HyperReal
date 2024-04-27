// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class AEnemy_BaseWeapon;
class UEnemyAnimInstance;

UCLASS()
class CAPSTONE20_HYPERREAL_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	bool IsSpawned;

	UPROPERTY(EditAnywhere)
	bool CanAttack;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy_BaseWeapon> EnemyWeaponClass;

	UPROPERTY(VisibleAnywhere)
	AEnemy_BaseWeapon* Weapon;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* SpawnAnimMontage;

protected:
	class UEnemyAnimInstance* AnimInstance;
	
public:
	bool GetIsSpawned() {return IsSpawned;}
	void SetIsSpawned(bool _spawn) { IsSpawned = _spawn; }
	bool GetCanAttack() { return CanAttack; }
	void SetCanAttack(bool _attack) { CanAttack = _attack; }
	AEnemy_BaseWeapon* GetWeapon() { return Weapon; }
	void AttackMelee();

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
