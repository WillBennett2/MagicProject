// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PlayerStatUIWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS(Abstract)
class MAGICPROJECT_API UPlayerStatUIWidget : public UBaseWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
public:
	virtual void NativeConstruct() override;
	void UpdateHealthBar(float value);
};
