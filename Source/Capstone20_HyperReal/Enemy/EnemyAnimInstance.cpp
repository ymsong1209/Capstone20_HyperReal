// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "BaseEnemy.h"

void UEnemyAnimInstance::AnimNotify_Attack()
{
    ABaseEnemy* Owner = Cast<ABaseEnemy>(TryGetPawnOwner());
    if (Owner)
    {
        Owner->AttackMelee();
    }
}
