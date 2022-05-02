// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicProjectile.h"
#include "Weapon_Base.h"
//#include "MagicProject/"
#include "Weapon_Projectile.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MAGICPROJECT_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Projectile")
	TSubclassOf<AMagicProjectile> m_Projectile;
	
public:
	virtual bool Fire_Implementation() override;
	
};
