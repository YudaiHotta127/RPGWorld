// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

//GameEffectのModifiersのカスタマイズした計算を用いる
//複数の計算を使用したい場合は、別の修飾子を追加し変更する必要がある
UCLASS()
class RPGWORLD_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
