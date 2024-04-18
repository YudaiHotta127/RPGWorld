// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

//GameEffect��Modifiers�̃J�X�^�}�C�Y�����v�Z��p����
//�����̌v�Z���g�p�������ꍇ�́A�ʂ̏C���q��ǉ����ύX����K�v������
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
