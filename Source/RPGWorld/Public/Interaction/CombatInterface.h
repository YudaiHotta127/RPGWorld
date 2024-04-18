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
	//Interfaceにプレイヤーのレベルを取得する関数を作成する
	virtual int32 GetPlayerLevel();
	//武器から魔法をとばすソケットの場所をとってくる
	virtual FVector GetCombatSocketLocation();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;
};
