// Fill out your copyright notice in the Description page of Project Settings.


#include "GameruleManager_Target.h"

#include "EngineUtils.h"
#include "Components//BillboardComponent.h"
#include "Target.h"


AGameruleManager_Target::AGameruleManager_Target()
{
	m_Root = CreateDefaultSubobject<UBillboardComponent>(TEXT("Root"));
	RootComponent = m_Root;
}


void AGameruleManager_Target::BeginPlay()
{
	if(m_Targets.Num()==0)
	{
		for(TActorIterator<ATarget> It(GetWorld()); It; ++It)
		{
			m_Targets.AddUnique(*It);
		}
	}

	for(ATarget* targ:m_Targets)
	{
		targ->onTargetDead.AddDynamic(this, &AGameruleManager_Target::TargetHit);
	}
	m_AmountRemaining = m_Targets.Num();
	
	Super::BeginPlay();
}

void AGameruleManager_Target::TargetHit_Implementation(int targetValue, AController* causer)
{
	m_AmountRemaining--;

	OnGameruleScorePoints.Broadcast(this,targetValue,causer);
	
	if(m_AmountRemaining==0)
	{
		BroadcastGameruleSuccess();
	}
	
}
