// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGAttributeSet.h"
#include "HealthSet.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UHealthSet : public UAGAttributeSet
{
	GENERATED_BODY()
	
public:
	UHealthSet();

	ATTRIBUTE_ACCESSORS(UHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthSet, Damage);
	ATTRIBUTE_ACCESSORS(UHealthSet, Heal);

public:
	mutable FAttributeChangedEvent OnHealthChanged;
	mutable FAttributeChangedEvent OnMaxHealthChanged;
	mutable FAttributeChangedEvent OnOutOfHealth;

protected:

	// Attribute 데이터 전처리, 변경 전 값 저장
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	// Attribute 바꼈을 때 추가 처리 로직 (ex. HP 0되면 사망)
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	UPROPERTY()
	FGameplayAttributeData Health;
	UPROPERTY()
	FGameplayAttributeData MaxHealth;

	// Meta Attribute
	UPROPERTY()
	FGameplayAttributeData Damage;
	UPROPERTY()
	FGameplayAttributeData Heal;

	float HealthBeforeChange;
	float MaxHealthBeforeChange;
	bool bIsOutOfHealth;
};
