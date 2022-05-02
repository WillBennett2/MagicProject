// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDeadSignature, int, pointValue, AController*, pointScorer);
UCLASS(Abstract)
class MAGICPROJECT_API ATarget : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UHealthComponent* m_HealthComp;
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDeadSignature onTargetDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_PointsValue;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void TargetDead(AController* causer);


};
