// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

//GameEffectのModifiersのカスタマイズした計算を用いる
//複数の計算を使用したい場合は、別の修飾子を追加し変更する必要がある
UCLASS()
class RPGWORLD_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntDef;
	
};
