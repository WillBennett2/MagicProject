// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "HealthComponent.h"

// Sets default values
ATarget::ATarget()
{
	m_HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	m_HealthComp->onComponentDead.AddDynamic(this,&ATarget::TargetDead);
	Super::BeginPlay();
	
}

void ATarget::TargetDead(AController* causer)
{
	onTargetDead.Broadcast(m_PointsValue, causer);

	//TODO Make this look fancy
	Destroy();
}


