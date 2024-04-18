// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "RPGAbilitySystemGlobals.generated.h"

/**
 * MakeEffectContext()Ç≈ê∂ê¨
 */
UCLASS()
class RPGWORLD_API URPGAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext()const override;
};
