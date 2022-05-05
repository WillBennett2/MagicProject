// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatUIWidget.h"

#include "Components/ProgressBar.h"

void UPlayerStatUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(HealthBar)
	{
		HealthBar->SetPercent(1);
	}
}

void UPlayerStatUIWidget::UpdateHealthBar(float value)
{
	HealthBar->SetPercent(value);
}
