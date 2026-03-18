// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ActionGameHealthComponent.h"

UActionGameHealthComponent::UActionGameHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UActionGameHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	if (InASC == nullptr) return false;

	AbilitySystem = InASC;

	HealthSet = Cast<UHealthSet>(AbilitySystem->GetAttributeSet(UHealthSet::StaticClass()));
	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);

	return true;
}

void UActionGameHealthComponent::UninitializeFromAbilitySystem()
{
	if (HealthSet != nullptr)
	{
		HealthSet->OnHealthChanged.RemoveAll(this);
		HealthSet->OnMaxHealthChanged.RemoveAll(this);
		HealthSet->OnOutOfHealth.RemoveAll(this);
	}

	HealthSet = nullptr;
	AbilitySystem = nullptr;
}

void UActionGameHealthComponent::HandleHealthChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(Instigator, Causer, EffectSpec, EffectMagnitude, OldValue, NewValue);
}

void UActionGameHealthComponent::HandleMaxHealthChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(Instigator, Causer, EffectSpec, EffectMagnitude, OldValue, NewValue);
}

void UActionGameHealthComponent::HandleOutOfHealth(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnDeath.Broadcast(GetOwner());
}

float UActionGameHealthComponent::GetHealth() const
{
	return HealthSet->GetHealth();
}

float UActionGameHealthComponent::GetMaxHealth() const
{
	return HealthSet->GetMaxHealth();
}