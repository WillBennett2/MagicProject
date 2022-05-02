// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(LogWeaponProj,Display,TEXT("Firing projectile weapon class"));
	UWorld* const world = GetWorld();
	if(world == nullptr||m_Projectile==nullptr)
	{
		return false;
	}

	UArrowComponent* firePoint = GetFirePoint();
	FVector spawnLocation = ((firePoint != nullptr)? firePoint->GetComponentLocation():GetActorLocation());
	FRotator spawnRotation = ((firePoint != nullptr)? firePoint->GetComponentRotation():GetActorRotation());

	FActorSpawnParameters actorSpawnParam;
	actorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AActor* parentActor = GetParentActor();
	actorSpawnParam.Owner = parentActor;
	actorSpawnParam.Instigator = Cast<APawn>(parentActor);

	world->SpawnActor<AMagicProjectile>(m_Projectile,spawnLocation,spawnRotation,actorSpawnParam);
	//return Super::Fire_Implementation();
	return true;
}
