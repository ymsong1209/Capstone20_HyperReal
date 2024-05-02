// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "Building.generated.h"

class AMonster;
UCLASS()
class CAPSTONE20_HYPERREAL_API ABuilding : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBuildingInfo mInfo;

	FString mDataTableKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TArray<UStaticMesh*> mMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMonster>> mMonsterClasses;
	
	TArray<class AMonster*> mMonsterVector;
	
	int		mCurPhase;
	float	mAccTime;
	float	mTotalTime;
	bool	mbActivated;//공격받기 전엔 비활성화
	bool	mbIsInvincible;


public:
	const FBuildingInfo& GetBuildingInfo() const {
		return mInfo;
	}
public:
	// Sets default values for this pawn's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Activate();
	void SpawnMonster();
	void RemoveMonster(class AMonster* monster);
	void KillAllMonsters();
	void Death();

public:
	virtual void Attack();

};
