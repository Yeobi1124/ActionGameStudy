// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_SixParams(FAttributeChangedEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, FGameplayEffectSpec /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/)

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UAGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
};
