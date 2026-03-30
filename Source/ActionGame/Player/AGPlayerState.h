// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API AAGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAGPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystem; }

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
};
