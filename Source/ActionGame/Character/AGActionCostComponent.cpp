// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AGActionCostComponent.h"

#include "AbilitySystem/Attribute/ActionCostSet.h"
#include "ActionGame.h"

UAGActionCostComponent::UAGActionCostComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UAGActionCostComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	if (InASC == nullptr) return false;

	ActionCostSet = Cast<UActionCostSet>(InASC->GetAttributeSet(UActionCostSet::StaticClass()));
	if (ActionCostSet == nullptr)
	{
		UE_LOG(LogActionGame, Warning, TEXT("ActionCostSet not found."));
		return false;
	}

	AbilitySystem = InASC;

	ActionCostSet->OnActionCostChanged.AddUObject(this, &ThisClass::HandleActionCostChanged);
	ActionCostSet->OnMaxActionCostChanged.AddUObject(this, &ThisClass::HandleMaxActionCostChanged);

	return true;
}

void UAGActionCostComponent::UninitializeFromAbilitySystem()
{
	if (ActionCostSet != nullptr)
	{
		ActionCostSet->OnActionCostChanged.RemoveAll(this);
		ActionCostSet->OnMaxActionCostChanged.RemoveAll(this);
	}

	AbilitySystem = nullptr;
	ActionCostSet = nullptr;
}

float UAGActionCostComponent::GetActionCost() const
{
	if (ActionCostSet == nullptr) return 0;
	return ActionCostSet->GetActionCost();
}

float UAGActionCostComponent::GetMaxActionCost() const
{
	if (ActionCostSet == nullptr) return 0;
	return ActionCostSet->GetMaxActionCost();
}

void UAGActionCostComponent::HandleActionCostChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnActionCostChanged.Broadcast(Instigator, EffectMagnitude, OldValue, NewValue);
}

void UAGActionCostComponent::HandleMaxActionCostChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnMaxActionCostChanged.Broadcast(Instigator, EffectMagnitude, OldValue, NewValue);
}
