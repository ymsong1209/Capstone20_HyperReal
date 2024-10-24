// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Components/Widget.h"
#include "GameData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	Knight,
	Archer,
	Magicion,
	End
};

UENUM(BlueprintType)
enum class EPlayerUpgradeType : uint8
{
	None,
	Attack,
	Health,
	Soul,
	End
};

UENUM(BlueprintType)
enum class ERuneType : uint8
{
	Rotation,
	Lightning,
	Extreme,
	Demolition,
	Dash,
	Drain,
	Haste,
	Thorn,
	Distortion,
	Resurrection,
	End
};

USTRUCT(BlueprintType)
struct FPlayerDataTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FPlayerDataTableInfo()
		: Job(EPlayerJob::End),
		  Attack(0),
		  Armor(0),
		  HP(0),
		  SP(0),
		  TotalGold(0),
		  LevelAccGold(0),
		  ASkillRatio(0.0f),
		  SSkillRatio(0.0f),
		  DSkillRatio(0.0f),
		  FSkillRatio(0.0f),
		  ASkillMaxCooltime(0.0f),
		  SSkillMaxCooltime(0.0f),
		  DSkillMaxCooltime(0.0f),
		  FSkillMaxCooltime(0.0f),
		  AttackSpeed(0.0f),
		  MoveSpeed(0.0f),
		  CriticalRatio(0.0f),
		  CriticalDamage(0.0f),
		  DrainRatio(0.0f),
		  CoolDownRatio(0.0f),
		  AttackLevel(0),
		  HealthLevel(0),
		  SoulLevel(0),
		  AttackProgress(0.0f),
		  HealthProgress(0.0f),
		  SoulProgress(0.0f)
	{
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob		Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		TotalGold;

	//현재 레벨에서 벌어들인 골드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		LevelAccGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		ASkillRatio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SSkillRatio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DSkillRatio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		FSkillRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		ASkillMaxCooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SSkillMaxCooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DSkillMaxCooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		FSkillMaxCooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalDamage;

	// 흡혈량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DrainRatio;

	// 스킬 쿨타임 감소량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CoolDownRatio;

	// 공격 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		AttackLevel;

	// 체력 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HealthLevel;

	// 마나 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		SoulLevel;

	// 공격 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackProgress;

	// 체력 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		HealthProgress;

	// 마나 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SoulProgress;
};


USTRUCT(BlueprintType)
struct FMonsterDataTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FMonsterDataTableInfo()
		: Attack(0),
		  Armor(0),
		  HP(0),
		  MP(0),
		  AttackSpeed(0.0f),
		  MoveSpeed(0.0f),
		  CriticalRatio(0.0f),
		  CriticalDamage(0.0f),
		  TraceDistance(0.0f),
		  AttackDistance(0.0f),
		  Level(0),
		  Exp(0),
		  Gold(0)
	{
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Gold;
};


USTRUCT(BlueprintType)
struct FBuildingDataTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FBuildingDataTableInfo()
		: Attack(0),
		  Armor(0),
		  HP(0),
		  MP(0),
		  AttackSpeed(0.0f),
		  SpawnIntervalSeconds(0.0f),
		  MonstersPerSpawn(0.0f),
		  MinSpawnRadius(0.0f),
		  MaxSpawnRadius(0.0f),
		  MaxSpawnMonsterCount(0),
		  Level(0),
		  Exp(0),
		  Gold(0)
	{
		PhaseTriggerHP.Empty();
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SpawnIntervalSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MonstersPerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MinSpawnRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MaxSpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxSpawnMonsterCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<float> PhaseTriggerHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Gold;
	
};


USTRUCT(BlueprintType)
struct FRuneDataTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FRuneDataTableInfo() :
		Level1Value(0.f),
		Level2Value(0.f),
		Level3Value(0.f),
		Level4Value(0.f),
		Level5Value(0.f)
	{
	}

public:
	// Rune Name or "Rune Cost"(Rune Upgrade cost per level)  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level1Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level2Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level3Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level4Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level5Value;
};


/// =====================================
/// 실제로 코드에서 불러들여서 사용할 구조체
/// =====================================


USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FPlayerInfo()
		: Job(EPlayerJob::End),
		  Attack(0),
		  Armor(0),
		  HP(0),
		  MaxHP(0),
		  SP(0),
		  MaxSP(0),
		  AttackSpeed(0.0f),
		  MoveSpeed(0.0f),
		  CriticalRatio(0.0f),
		  CriticalDamage(0.0f),
		  ASkillRatio(0.0f),
		  SSkillRatio(0.0f),
		  DSkillRatio(0.0f),
		  FSkillRatio(0.0f),
		  ASkillmaxcooltime(0.0f),
		  SSkillmaxcooltime(0.0f),
		  DSkillmaxcooltime(0.0f),
		  FSkillmaxcooltime(0.0f),
		  Level(0),
		  Exp(0),
		  TotalGold(0),
		  LevelAccGold(0),
		  DrainRatio(0.0f),
		  CoolDownRatio(0.0f),
		  AttackLevel(0),
		  HealthLevel(0),
		  SoulLevel(0),
		  AttackProgress(0.0f),
		  HealthProgress(0.0f),
		  SoulProgress(0.0f)
	{
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob		Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxSP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		ASkillRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SSkillRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DSkillRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		FSkillRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		ASkillmaxcooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SSkillmaxcooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DSkillmaxcooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		FSkillmaxcooltime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		TotalGold;

	//현재 레벨에서 벌어들인 골드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		LevelAccGold;

	// 흡혈량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		DrainRatio;

	// 스킬 쿨타임 감소량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CoolDownRatio;

	// 공격 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		AttackLevel;

	// 체력 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HealthLevel;

	// 마나 강화 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		SoulLevel;

	// 공격 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackProgress;

	// 체력 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		HealthProgress;

	// 마나 강화 진행도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SoulProgress;
};

USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FMonsterInfo()
		: Attack(0),
		  Armor(0),
		  HP(0),
		  MaxHP(0),
		  MP(0),
		  MaxMP(0),
		  AttackSpeed(0.0f),
		  MoveSpeed(0.0f),
		  CriticalRatio(0.0f),
		  CriticalDamage(0.0f),
		  TraceDistance(0.0f),
		  AttackDistance(0.0f),
		  Level(0),
		  Exp(0),
		  Gold(0)
	{
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Gold;
};


USTRUCT(BlueprintType)
struct FBuildingInfo
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FBuildingInfo()
		: Attack(0),
		  Armor(0),
		  HP(0),
		  MaxHP(0),
		  MP(0),
		  MaxMP(0),
		  AttackSpeed(0.0f),
		  SpawnIntervalSeconds(0.0f),
		  MonstersPerSpawn(0.0f),
		  MinSpawnRadius(0.0f),
		  MaxSpawnRadius(0.0f),
		  MaxSpawnMonsterCount(0),
		  Level(0),
		  Exp(0),
		  Gold(0)
	{
		PhaseTriggerHP.Empty();
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		HP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SpawnIntervalSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MonstersPerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<float> PhaseTriggerHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MinSpawnRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		MaxSpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		MaxSpawnMonsterCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Gold;
};

USTRUCT(BlueprintType)
struct FRuneInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Constructor to initialize all member variables with default values
	FRuneInfo() :
		Level1Value(0.f),
		Level2Value(0.f),
		Level3Value(0.f),
		Level4Value(0.f),
		Level5Value(0.f)
	{
	}

public:
	// Rune Name or "Rune Cost"(Rune Upgrade cost per level)  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level1Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level2Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level3Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level4Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Level5Value;
};

UCLASS()
class CAPSTONE20_HYPERREAL_API UGameData : public UObject
{
	GENERATED_BODY()
	

};
template<typename TEnum>
FString EnumToString(TEnum EnumValue)
{
	const UEnum* EnumPtr = StaticEnum<TEnum>();
	if (!EnumPtr)
	{
		return FString("Invalid");
	}
	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
}
