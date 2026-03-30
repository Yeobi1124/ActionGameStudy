// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilitySystemConnector.h"

#include "Character/ActionGameCharacter.h"
#include "Player/AGPlayerState.h"
#include "AbilitySystem/InitializeWithAbilitySystem.h"

UAbilitySystemConnector::UAbilitySystemConnector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void UAbilitySystemConnector::InitializeComponent()
{
	Super::InitializeComponent();

	AActionGameCharacter* Character = Cast<AActionGameCharacter>(GetOwner());

	if (Character != nullptr)
	{
		Character->OnPlayerStateConnected.AddDynamic(this, &ThisClass::HandlePlayerStateConnected);
	}
}

void UAbilitySystemConnector::HandlePlayerStateConnected(APlayerState* NewPlayerState)
{
	AAGPlayerState* AGPS = Cast<AAGPlayerState>(NewPlayerState);

	if (AGPS != nullptr)
	{
		TSet<UActorComponent*> Components = GetOwner()->GetComponents();

		for (UActorComponent* Component : Components)
		{
			IInitializeWithAbilitySystem* Comp = Cast<IInitializeWithAbilitySystem>(Component);

			if (Comp != nullptr)
			{
				Comp->InitializeWithAbilitySystem(AGPS->GetAbilitySystemComponent());
			}
		}
	}
}

