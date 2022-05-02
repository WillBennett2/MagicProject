// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameruleManager.generated.h"
class AGameruleManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameruleSuccessSignature,  AGameruleManager*, delegateInstigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameruleSorePointsSignature,  AGameruleManager*, delegateInstigator, int, points, AController*, pointScorer);


UCLASS()
class MAGICPROJECT_API AGameruleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameruleManager();

	UPROPERTY(BlueprintAssignable)
	FGameruleSuccessSignature OnGameruleSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FGameruleSorePointsSignature OnGameruleScorePoints;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsMatchEndingRule;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BroadcastGameruleSuccess();

};
