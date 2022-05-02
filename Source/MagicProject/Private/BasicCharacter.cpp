// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"

#include "Fireable.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);

	//set rates for inputs
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f,1.75f,64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	m_ChildActor_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSlot"));
	m_ChildActor_Gun->SetupAttachment(FirstPersonCameraComponent);
	
	m_ChildActor_ProjectileGun = CreateDefaultSubobject<UChildActorComponent>(TEXT("ProjectileGunSlot"));
	m_ChildActor_ProjectileGun->SetupAttachment(FirstPersonCameraComponent);
	m_ChildActor_HitscanGun = CreateDefaultSubobject<UChildActorComponent>(TEXT("HitScanGunSlot"));
	m_ChildActor_HitscanGun->SetupAttachment(FirstPersonCameraComponent);

}

void ABasicCharacter::JumpPressed_Implementation()
{
	IInputable::JumpPressed_Implementation();
	Jump();
}

void ABasicCharacter::JumpReleased_Implementation()
{
	IInputable::JumpReleased_Implementation();
	StopJumping();
}

void ABasicCharacter::FirePressed_Implementation()
{
	
	//IInputable::FirePressed_Implementation();
	AActor* child = m_ChildActor_Gun ->GetChildActor();

	if(UKismetSystemLibrary::DoesImplementInterface(child,UFireable::StaticClass()))
	{
		IFireable::Execute_Fire(child);
	}
}

void ABasicCharacter::FireReleased_Implementation()
{
	//IInputable::FireReleased_Implementation();
	
}

void ABasicCharacter::OnePressed_Implementation()
{
	m_ChildActor_Gun = m_ChildActor_ProjectileGun;
	IInputable::OnePressed_Implementation();
}

void ABasicCharacter::TwoPressed_Implementation()
{
	//m_ChildActor_Gun->GetChildComponent(UChildActorComponent::ChildActorClass) = m_ChildActor_ProjectileGun;
	IInputable::TwoPressed_Implementation();
}

void ABasicCharacter::MoveForward_Implementation(float Value)
{
	IInputable::MoveForward_Implementation(Value);
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(),Value);
	}
}

void ABasicCharacter::MoveRight_Implementation(float Value)
{
	IInputable::MoveRight_Implementation(Value);
	
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(),Value);
	}
}

void ABasicCharacter::LookUp_Implementation(float Value)
{
	IInputable::LookUp_Implementation(Value);
	AddControllerPitchInput(Value);
}

void ABasicCharacter::Turn_Implementation(float Value)
{
	IInputable::Turn_Implementation(Value);
	AddControllerYawInput(Value);
}

void ABasicCharacter::LookUpRate_Implementation(float Rate)
{
	IInputable::LookUpRate_Implementation(Rate);
	AddControllerPitchInput(Rate*BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABasicCharacter::TurnAtRate_Implementation(float Rate)
{
	IInputable::TurnAtRate_Implementation(Rate);
	AddControllerPitchInput(Rate*BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


