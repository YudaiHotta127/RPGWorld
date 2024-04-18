// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class UAnimMontage;


class RPGWORLD_API ICombatInterface
{
	GENERATED_BODY()
public:
	//Interface�Ƀv���C���[�̃��x�����擾����֐����쐬����
	virtual int32 GetPlayerLevel();
	//���킩�疂�@���Ƃ΂��\�P�b�g�̏ꏊ���Ƃ��Ă���
	virtual FVector GetCombatSocketLocation();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;
};
