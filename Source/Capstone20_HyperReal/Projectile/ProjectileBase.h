// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_Particle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* m_Niagara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float m_fMaxDistance;

	AController* m_OwnerController;

	FVector m_PrevLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_Damage;

	AActor* m_Target;

public:
	void SetTarget(AActor* Target)
	{
		m_Target = Target;
	}
	
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

	float GetDamage() { return m_Damage; }

	void SetOwnerController(AController* Controller)
	{
		m_OwnerController = Controller;
	}
private:
	float m_fAccDistance;
	
public:
	UFUNCTION()
	void CollisionStop(const FHitResult& ImpactResult);
	UFUNCTION()
	void CollisionBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

protected:
	virtual void ProjectileStop(const FHitResult& ImpactResult);
	virtual void ProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
