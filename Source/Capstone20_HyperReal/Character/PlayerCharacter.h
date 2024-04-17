// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPlayerAnimInstance;
class UInputMappingContext;
class UInputAction;
class FActionInputInstance;

enum class EPlayerSkill
{
	SkillA,
	SkillS,
	SkillD,
	SkillF,
	None
};

UCLASS()
class CAPSTONE20_HYPERREAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	// 액션 바인딩
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SkillAAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SkillSAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SkillDAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SkillFAction;

	// 공격 애니메이션 몽타주 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<UAnimMontage*> m_arrAttackMontage;

	// 재생 시킬 애니메이션 인덱스
	int32 m_iAttackMontageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float m_fAttackImpulse;

protected:
	class UPlayerAnimInstance* m_pAnim;
	bool m_bOnAttack;

	bool m_bComboDetected;

	EPlayerSkill m_eUsingSkill;

public:
	bool OnAttack() const { return m_bOnAttack; };
	void SetAttack(bool _bAttack) { m_bOnAttack = _bAttack; }

	bool IsComboDectected() { return m_bComboDetected; }

	EPlayerSkill GetUsingSkill() { return m_eUsingSkill; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	virtual void Attack();
	virtual void AttackEnd();
	virtual void AttackReset();
};
