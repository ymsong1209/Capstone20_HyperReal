// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPlayerAnimInstance;
class UInputMappingContext;
class UInputAction;
class FActionInputInstance;
class UInGameUserWidget;

UCLASS()
class CAPSTONE20_HYPERREAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	FString m_strDataTableKey;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* EscapeAction;
	
	// 공격 애니메이션 몽타주 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<UAnimMontage*> m_arrAttackMontage;

	// 재생 시킬 애니메이션 인덱스
	int32 m_iAttackMontageIndex;

	// 공격시 살짝 이동할 힘
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float m_fAttackImpulse;

	// 고스트 트레일 생성 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	float m_fGhostTrailTickTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* m_NSEffect01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UMaterialInterface* m_pBlinkOverlayInterface;

protected:
	class UPlayerAnimInstance* m_pAnim;
	bool	m_bIsDead;

	bool m_bOnAttack;

	bool m_bComboDetected;

	EPlayerSkill m_eUsingSkill;

	float m_fAnimPlaySpeed;

	bool m_bGhostTrail;

	USkeletalMesh* m_SKMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* m_MIDBlinkOverlay;

	UInGameUserWidget* m_pHUDWidget;

	float m_faccSkillACool;

	float m_faccSkillSCool;

	float m_faccSkillDCool;

	float m_faccSkillFCool;

private:
	float m_fDefaultSpeed;
	float m_fDefaultAccel;
	float m_fAccGhostTime;
	bool  m_bInvincible;

private:
	class APortal* m_pPortal;

public:
	bool IsDead() { return m_bIsDead; }

	bool OnAttack() const { return m_bOnAttack; };
	void SetAttack(bool _bAttack) { m_bOnAttack = _bAttack; }

	bool IsComboDectected() { return m_bComboDetected; }

	EPlayerSkill GetUsingSkill() { return m_eUsingSkill; }

	float GetAnimPlaySpeed() { return m_fAnimPlaySpeed * GetAttackSpeed(); }
	void SetAnimPlaySpeed(float _fSpeed) { m_fAnimPlaySpeed = _fSpeed; }

	bool IsInvincible() const {return m_bInvincible;}
	void SetInvincible(bool _invincible){m_bInvincible = _invincible;}

	FPlayerInfo& GetPlayerInfo();

	// 기본 스탯 외 추가 옵션 계산용 Getter
	int32 GetHPMax();
	int32 GetSPMax();

	int32 GetAttack();
	int32 GetArmor();

	float GetAttackSpeed();
	float GetMoveSpeed();

	float GetCoolDown();

	class URuneManager* GetRuneManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual float GiveDamage(AActor* _Target, float _fAttackRatio, EPlayerSkill _type);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	virtual void Attack();
	virtual void AttackCombo();
	virtual void AttackEnd();
	virtual void AttackReset();

	virtual void SkillEnd() {};
	virtual void SpawnGhostTrail();

	FVector GetMousePosition();

	virtual void EscapeFunction();

public:
	// 감속하거나 가속할 배율 입력
	void ChangeWalkSpeed(float _value);
	void SetPortal(class APortal* _portal) { m_pPortal = _portal; };

	void Heal(float fValue);
	void Ressurection(float fValue);
	virtual void SetDead(bool _bState) {};

private:
	void InitPlayerData();
	
	void TestBasecampUI();
};
