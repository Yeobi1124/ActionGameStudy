// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AGPlayerState.h"

#include "AbilitySystemComponent.h"

AAGPlayerState::AAGPlayerState()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
}
