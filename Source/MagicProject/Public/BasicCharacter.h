// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class UChildActorComponent;

UCLASS(Config=Game)
class MAGICPROJECT_API ABasicCharacter : public ACharacter, public IInputable
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* m_ChildActor_ProjectileGun;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* m_ChildActor_HitscanGun;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* m_ChildActor_Gun;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
public:
	// Sets default values for this character's properties
	ABasicCharacter();

#pragma region IInputable_interface
	
	virtual void JumpPressed_Implementation() override;
	virtual void JumpReleased_Implementation()override;
	virtual void FirePressed_Implementation()override;
	virtual void FireReleased_Implementation()override;

	virtual void OnePressed_Implementation() override;
	virtual void TwoPressed_Implementation() override;
	
	virtual void MoveForward_Implementation(float Value)override;
	virtual void MoveRight_Implementation(float Value)override;
	virtual void LookUp_Implementation(float Value)override;
	virtual void Turn_Implementation(float Value)override;
	virtual void LookUpRate_Implementation(float Rate)override;
	virtual void TurnAtRate_Implementation(float Rate)override;

#pragma endregion 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera)
	float BaseLookUpRate;
	
	
};
