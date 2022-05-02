// Copyright Epic Games, Inc. All Rights Reserved.


#include "MagicProjectGameModeBase.h"

#include "EngineUtils.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialExpressionCustom.h"

AMagicProjectGameModeBase::AMagicProjectGameModeBase(): Super()
{
	m_CountDownTimer = 3;
}

AActor* AMagicProjectGameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(m_PlayerStarts.Num()==0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),m_PlayerStarts);
	}
	if(m_PlayerStarts.Num()>0)
	{
		return m_PlayerStarts[0];
	}
	else
	{
		return nullptr;
	}
	//return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

void AMagicProjectGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	m_PlayerControllers.AddUnique(NewPlayer);
	APlayerController* castedPC = Cast<APlayerController>(NewPlayer);
	if(castedPC!=nullptr)
	{
		//TODO bind to any relevent events
		//player deaths
		castedPC->InitializeComponents();
	}
	Super::PostLogin(NewPlayer);
}

void AMagicProjectGameModeBase::Logout(AController* Exiting)
{
	m_PlayerControllers.Remove(Exiting);
	APlayerController* castedPC = Cast<APlayerController>(Exiting);
	if(castedPC!=nullptr)
	{
		//TODO: unbined from events
	}
	Super::Logout(Exiting);
}

void AMagicProjectGameModeBase::DecreaseCountDown()
{
	m_CountDownTimer--;
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("%d"),m_CountDownTimer));
	
	if(m_CountDownTimer==0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountDown,this,&AMagicProjectGameModeBase::DecreaseCountDown,1.f,false);
	}
}

void AMagicProjectGameModeBase::HandleGameruleSuccess(AGameruleManager* delegateInstigator)
{
	if(m_GameruleManagers.Find(delegateInstigator))
	{
		EndMatch();
	}
	else
	{
		m_GamerulesLeft--;
		if(m_GamerulesLeft==0)
		{
			EndMatch();
		}
	}
}

void AMagicProjectGameModeBase::HandleGameruleSorePoints(AGameruleManager* delegateInstigator, int points,
	AController* pointScorer)
{
	int index = m_PlayerControllers.Find(pointScorer);
	if(index != -1)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Orange,FString::Printf(TEXT("Adding %d points to player controller index %d"), points, index));
	}
}

void AMagicProjectGameModeBase::BeginPlay()
{
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(),0),true);//destroy brought pc
	UGameplayStatics::CreatePlayer(GetWorld());

	m_GamerulesLeft=0;
	for(TActorIterator<AGameruleManager>It(GetWorld());It; ++It)
	{
		m_GameruleManagers.Add(*It, It->IsMatchEndingRule);
		It->OnGameruleSuccess.AddDynamic(this,&AMagicProjectGameModeBase::HandleGameruleSuccess);
		It->OnGameruleScorePoints.AddDynamic(this, &AMagicProjectGameModeBase::AMagicProjectGameModeBase::HandleGameruleSorePoints);
		if(!It->IsMatchEndingRule)
		{
			m_GamerulesLeft++;
		}
	}
	//Super::BeginPlay();
}

void AMagicProjectGameModeBase::HandleMatchIsWaitingToStart()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("%d"),m_CountDownTimer));
	GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountDown,this,&AMagicProjectGameModeBase::DecreaseCountDown,1.f,false);
	Super::HandleMatchIsWaitingToStart();
}

void AMagicProjectGameModeBase::HandleMatchHasStarted()
{
	if(m_PlayingPawn!=nullptr)
	{
		DefaultPawnClass = m_PlayingPawn;
	}
	for(AController* controller:m_PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller,UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	Super::HandleMatchHasStarted();
}

void AMagicProjectGameModeBase::HandleMatchHasEnded()
{
	for(AController* controller:m_PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller,UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnd(controller);
		}
	}
	Super::HandleMatchHasEnded();
}

void AMagicProjectGameModeBase::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting to start";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Turquoise,FString::Printf(TEXT("State changed tp: %s"),*output));
	Super::OnMatchStateSet();
}

bool AMagicProjectGameModeBase::ReadyToStartMatch_Implementation()
{
	return false;
	//return Super::ReadyToStartMatch_Implementation();
}

bool AMagicProjectGameModeBase::ReadyToEndMatch_Implementation()
{
	return false;
	//return Super::ReadyToEndMatch_Implementation();
}
