// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICPROJECT_API AInGamePlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	virtual void Init_Implementation();

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnd_Implementation() override;
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PawnToSpawn;

private:
	void JumpPressed(); void JumpReleased();
	void FirePressed(); void FireReleased();

	void OnePressed();
	void TwoPressed();
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void TurnAtRate(float Rate);
	void LookUpRate(float Rate);
};
