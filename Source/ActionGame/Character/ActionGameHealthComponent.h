// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystem/Attribute/HealthSet.h"
#include "AbilitySystem/InitializeWithAbilitySystem.h"
#include "ActionGameHealthComponent.generated.h"

class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EDeathState : uint8
{
	NotDeath UMETA(DisplayName = "NotDeath"),
	StartDeath UMETA(DisplayName = "StartDeath"),
	FinishDeath UMETA(DisplayName = "FinishDeath")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FHealthChangedEvent, AActor*, EffectInstigator, AActor*, EffectCauser, FGameplayEffectSpec, EffectSpec, float, EffectMagnitude, float, OldValue, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UActionGameHealthComponent : public UActorComponent, public IInitializeWithAbilitySystem
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionGameHealthComponent();

	bool InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);
	void UninitializeFromAbilitySystem();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EDeathState GetDeathState() const { return DeathState; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDeath() const { return DeathState > EDeathState::NotDeath; }
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthChangedEvent OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthChangedEvent OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FDeathEvent OnDeath;

private:
	UFUNCTION()
	void HandleHealthChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue);
	UFUNCTION()
	void HandleMaxHealthChanged(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue);
	UFUNCTION()
	void HandleOutOfHealth(AActor* Instigator, AActor* Causer, FGameplayEffectSpec EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

private:
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	TObjectPtr<const UHealthSet> HealthSet;
	EDeathState DeathState;
};
