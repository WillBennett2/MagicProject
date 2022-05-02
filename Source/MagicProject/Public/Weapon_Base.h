// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UArrowComponent;

UCLASS(Abstract)
class MAGICPROJECT_API AWeapon_Base : public AActor, public IFireable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

	virtual bool Fire_Implementation() override; //comes from BP native event in Ufunction

	FORCEINLINE UArrowComponent* GetFirePoint() const{return m_FirePoint;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly);
	USceneComponent* m_Root;
	UPROPERTY(VisibleDefaultsOnly);
	USkeletalMeshComponent* m_GunMesh;
	UPROPERTY(VisibleDefaultsOnly);
	UArrowComponent* m_FirePoint;
};
