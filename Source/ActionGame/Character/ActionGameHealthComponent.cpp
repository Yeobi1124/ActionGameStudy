// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ActionGameHealthComponent.h"

#include "ActionGame.h"

UActionGameHealthComponent::UActionGameHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UActionGameHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	if (InASC == nullptr) return false;

	HealthSet = Cast<UHealthSet>(InASC->GetAttributeSet(UHealthSet::StaticClass()));
	if (HealthSet == nullptr)
	{
		UE_LOG(LogActionGame, Warning, TEXT("Health Set not found."));
		return false;
	}

	AbilitySystem = InASC;

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
	if (HealthSet == nullptr) return 0;
	return HealthSet->GetHealth();
}

float UActionGameHealthComponent::GetMaxHealth() const
{
	if (HealthSet == nullptr) return 0;
	return HealthSet->GetMaxHealth();
}