// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameruleManager.h"
#include "Target.h"
#include "GameruleManager_Target.generated.h"

class UBillboardComponent;
class ATarget;
UCLASS()
class MAGICPROJECT_API AGameruleManager_Target : public AGameruleManager
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UBillboardComponent* m_Root;


public:
	AGameruleManager_Target();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATarget*> m_Targets;

	int m_AmountRemaining;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void TargetHit(int targetValue, AController* causer);
	virtual void TargetHit_Implementation(int targetValue, AController* causer);
};
