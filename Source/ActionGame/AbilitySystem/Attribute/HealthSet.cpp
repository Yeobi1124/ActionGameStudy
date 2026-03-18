// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/HealthSet.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UHealthSet::UHealthSet() : Health(100), MaxHealth(100)
{
}

bool UHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data)) return;

	HealthBeforeChange = GetHealth();
	MaxHealthBeforeChange = GetMaxHealth();

	return false;
}

void UHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	// Execute Meta Attribute
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		float NewHealth = FMath::Clamp(GetHealth() - GetDamage(), 0, GetMaxHealth());
		SetHealth(NewHealth);
		SetDamage(0);
	}

	if (Data.EvaluatedData.Attribute == GetHealAttribute())
	{
		float NewHealth = FMath::Clamp(GetHealth() - GetHeal(), 0, GetMaxHealth());
		SetHealth(NewHealth);
		SetDamage(0);
	}

	// Event Broadcast
	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));

		OnMaxHealthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxHealthBeforeChange, GetMaxHealth());
	}

	if (GetHealth() != HealthBeforeChange)
	{
		OnHealthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeChange, GetHealth());
	}

	if (GetHealth() <= 0 && !bIsOutOfHealth)
	{
		OnOutOfHealth.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeChange, GetHealth());
	}

	bIsOutOfHealth = GetHealth() <= 0;
}
