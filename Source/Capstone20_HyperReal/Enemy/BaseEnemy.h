// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

//class AEnemy_BaseWeapon;

UCLASS()
class CAPSTONE20_HYPERREAL_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY()
	bool CanAttack;

	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<AEnemy_BaseWeapon> EnemyWeaponClass;

	//UPROPERTY(VisibleAnywhere)
	//AEnemy_BaseWeapon* Weapon;


public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCanAttack(bool _attack) {
		CanAttack = _attack;
	}

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool GetCanAttack() const { return CanAttack; }

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
