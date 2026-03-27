// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AGActionCostComponent.generated.h"

struct FGameplayEffectSpec;
class UAbilitySystemComponent;
class UActionCostSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FActionCostChangedEvent, AActor*, OwningActor, float, EffectMagnitude, float, OldValue, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UAGActionCostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAGActionCostComponent();

	bool InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);
	void UninitializeFromAbilitySystem();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetActionCost() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxActionCost() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FActionCostChangedEvent OnActionCostChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FActionCostChangedEvent OnMaxActionCostChanged;

private:
	void HandleActionCostChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue);
	void HandleMaxActionCostChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

private:
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	TObjectPtr<const UActionCostSet> ActionCostSet;
};
