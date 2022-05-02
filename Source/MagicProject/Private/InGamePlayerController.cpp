// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"

#include "Inputable.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AInGamePlayerController::AInGamePlayerController() : Super()
{
	
}
void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump",IE_Pressed,this,&AInGamePlayerController::JumpPressed);
	InputComponent->BindAction("Jump",IE_Released,this,&AInGamePlayerController::JumpReleased);
	InputComponent->BindAction("Fire",IE_Pressed,this,&AInGamePlayerController::FirePressed);
	InputComponent->BindAction("Fire",IE_Released,this,&AInGamePlayerController::FireReleased);

	InputComponent->BindAxis("MoveForward",this,&AInGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&AInGamePlayerController::MoveRight);
	InputComponent->BindAxis("Turn",this,&AInGamePlayerController::Turn);
	InputComponent->BindAxis("LookUp",this,&AInGamePlayerController::LookUp);
	InputComponent->BindAxis("TurnRate",this,&AInGamePlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUpRate",this,&AInGamePlayerController::LookUpRate);
}

void AInGamePlayerController::Init_Implementation()
{
	if(GetPawn()!=nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AInGamePlayerController::Handle_MatchStarted_Implementation()
{
	if(GetPawn()!=nullptr)
	{
		GetPawn()->Destroy();
	}
	UWorld* const world = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = ((tempStart!=nullptr) ? tempStart->GetActorLocation():FVector::ZeroVector);
	FRotator spawnRotation = ((tempStart!=nullptr) ? tempStart->GetActorRotation():FRotator::ZeroRotator);

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* tempPawn = world->SpawnActor<APawn>(UGameplayStatics::GetGameMode(world)->DefaultPawnClass,spawnLocation,spawnRotation,ActorSpawnParameters);

	//TODO add init implementaion
	Possess(tempPawn);
	//IMatchStateHandler::Handle_MatchStarted_Implementation();
}

void AInGamePlayerController::Handle_MatchEnd_Implementation()
{
	//set input mode
	//SetInputMode(FInputModeUIOnly());
	//IMatchStateHandler::Handle_MatchEnd_Implementation();
}

void AInGamePlayerController::JumpPressed()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpPressed(pawn);
	}
}

void AInGamePlayerController::JumpReleased()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpReleased(pawn);
	}
}

void AInGamePlayerController::FirePressed()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_FirePressed(pawn);
	}
}

void AInGamePlayerController::FireReleased()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_FireReleased(pawn);
	}
}

void AInGamePlayerController::OnePressed()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_OnePressed(pawn);
	}
}

void AInGamePlayerController::TwoPressed()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_TwoPressed(pawn);
	}
}

void AInGamePlayerController::MoveForward(float Value)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveForward(pawn,Value);
	}
}

void AInGamePlayerController::MoveRight(float Value)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveRight(pawn,Value);
	}
}

void AInGamePlayerController::Turn(float Value)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Turn(pawn,Value);
	}
}

void AInGamePlayerController::LookUp(float Value)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUp(pawn,Value);
	}
}

void AInGamePlayerController::TurnAtRate(float Rate)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_TurnAtRate(pawn,Rate);
	}
}

void AInGamePlayerController::LookUpRate(float Rate)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUpRate(pawn,Rate);
	}
}
