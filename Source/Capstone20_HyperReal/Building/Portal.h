// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class CAPSTONE20_HYPERREAL_API APortal : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	UStaticMeshComponent* BuildingMesh;
	
	// Collider component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	class UBoxComponent* Collider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	UDecalComponent* Decal;


public: 
	// Function to handle the overlap
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Function to transition to the next level
	void TransitionToNextLevel();
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
