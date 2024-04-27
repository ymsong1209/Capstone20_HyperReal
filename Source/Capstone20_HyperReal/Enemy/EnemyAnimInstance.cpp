// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "BaseEnemy.h"
#include "Enemy_BaseWeapon.h"
void UEnemyAnimInstance::AnimNotify_Attack()
{
    ABaseEnemy* Owner = Cast<ABaseEnemy>(TryGetPawnOwner());
    if (Owner)
    {
        Owner->AttackMelee();
    }
}

void UEnemyAnimInstance::AnimNotify_SpawnFinished()
{
    ABaseEnemy* Owner = Cast<ABaseEnemy>(TryGetPawnOwner());
    if (Owner)
    {
        Owner->SetCanAttack(true);
        Owner->SetIsSpawned(true);
        Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

        AEnemy_BaseWeapon* OwnerWeapon = Owner->GetWeapon();
        if (OwnerWeapon) {
            OwnerWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r_sword"));
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("Weapon Not Spawned"));
        }
    }
}

void UEnemyAnimInstance::AnimNotify_DrawFinished()
{
}
