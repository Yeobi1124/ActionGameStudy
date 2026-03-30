// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemConnector.generated.h"

class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UAbilitySystemConnector : public UPawnComponent, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitySystemConnector(const FObjectInitializer& ObjectInitializer);

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }

protected:
	void InitializeComponent() override;

private:
	UFUNCTION()
	void HandlePlayerStateConnected(APlayerState* NewPlayerState);

	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
};
