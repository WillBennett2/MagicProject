// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameruleManager.h"
#include "GameFramework/GameMode.h"
#include "MagicProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICPROJECT_API AMagicProjectGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AMagicProjectGameModeBase();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	TArray<AActor*> m_PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AController*> m_PlayerControllers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MatchManagement")
	int m_CountDownTimer;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MatchManagement")
	TSubclassOf<APawn> m_PlayingPawn;

	int m_GamerulesLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MatchManagement")
	TMap<AGameruleManager*, bool> m_GameruleManagers;
	
	FTimerHandle TimerDecreaseCountDown;
	UFUNCTION()
	void DecreaseCountDown();

	UFUNCTION()
	void HandleGameruleSuccess(AGameruleManager* delegateInstigator);
	UFUNCTION()
	void HandleGameruleSorePoints(AGameruleManager* delegateInstigator, int points,AController* pointScorer);
	
	virtual void BeginPlay() override;
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	//override so they dont get run
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	
};
