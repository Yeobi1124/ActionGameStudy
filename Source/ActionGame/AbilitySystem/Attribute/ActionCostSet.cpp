// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/ActionCostSet.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UActionCostSet::UActionCostSet() : ActionCost(100), MaxActionCost(100), ChangedActionCost(0)
{
}

bool UActionCostSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (Super::PreGameplayEffectExecute(Data) == false) return false;

	ActionCostBeforeChange = GetActionCost();
	MaxActionCostBeforeChange = GetMaxActionCost();

	return true;
}

void UActionCostSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	// Meta Attribute
	if (Data.EvaluatedData.Attribute == GetChangedActionCostAttribute())
	{
		SetActionCost(FMath::Clamp(GetActionCost() + GetChangedActionCost(), 0, GetMaxActionCost()));
		SetChangedActionCost(0);
	}

	// Broadcast
	if (GetMaxActionCost() == MaxActionCostBeforeChange)
	{
		OnMaxActionCostChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxActionCostBeforeChange, GetMaxActionCost());
	}

	if (GetActionCost() == ActionCostBeforeChange)
	{
		SetActionCost(FMath::Clamp(GetActionCost(), 0, GetMaxActionCost()));
		OnActionCostChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, ActionCostBeforeChange, GetActionCost());
	}
}
