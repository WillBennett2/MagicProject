// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICPROJECT_API IInputable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void JumpPressed();
	UFUNCTION(BlueprintNativeEvent)
	void JumpReleased();
	UFUNCTION(BlueprintNativeEvent)
	void FirePressed();
	UFUNCTION(BlueprintNativeEvent)
	void FireReleased();

	UFUNCTION(BlueprintNativeEvent)
	void SwitchPressed();

	
	UFUNCTION(BlueprintNativeEvent)
	void MoveForward(float Value);
	UFUNCTION(BlueprintNativeEvent)
	void MoveRight(float Value);
	UFUNCTION(BlueprintNativeEvent)
	void LookUp(float Value);
	UFUNCTION(BlueprintNativeEvent)
	void Turn(float Value);
	UFUNCTION(BlueprintNativeEvent)
	void LookUpRate(float Rate);
	UFUNCTION(BlueprintNativeEvent)
	void TurnAtRate(float Rate);
};
