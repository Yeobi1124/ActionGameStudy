// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGAttributeSet.h"
#include "ActionCostSet.generated.h"

/**
 * It's for mana, stamina
 */
UCLASS()
class ACTIONGAME_API UActionCostSet : public UAGAttributeSet
{
	GENERATED_BODY()
	
public:
	UActionCostSet();

	ATTRIBUTE_ACCESSORS(UActionCostSet, ActionCost);
	ATTRIBUTE_ACCESSORS(UActionCostSet, MaxActionCost);
	ATTRIBUTE_ACCESSORS(UActionCostSet, ChangedActionCost);

public:
	mutable FAttributeChangedEvent OnActionCostChanged;
	mutable FAttributeChangedEvent OnMaxActionCostChanged;

protected:
	// Attribute 데이터 전처리, 변경 전 값 저장
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	// Attribute 바꼈을 때 추가 처리 로직 (ex. HP 0되면 사망)
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	UPROPERTY()
	FGameplayAttributeData ActionCost;

	UPROPERTY()
	FGameplayAttributeData MaxActionCost;

	// Meta attribute
	UPROPERTY()
	FGameplayAttributeData ChangedActionCost;

	float ActionCostBeforeChange;
	float MaxActionCostBeforeChange;
};
