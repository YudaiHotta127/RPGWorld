// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * ExecutionCalculation‚Í•¡”‚ÌAttribute‚ğ•ÏX‚Å‚«‚é‚ª
 * ModMagnitudeCalculation‚Í‚Å‚«‚È‚¢
 */
UCLASS()
class RPGWORLD_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
