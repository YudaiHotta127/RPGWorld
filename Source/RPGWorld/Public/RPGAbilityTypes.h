#pragma once

#include "GameplayEffectTypes.h"
#include "RPGAbilityTypes.generated.h"


USTRUCT(BlueprintType)
struct FRPGGameplayEffectContext :public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit()const { return bIsCriticalHit; }
	bool IsBlockedHit()const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }

	//シリアル化に使用される実際の構造体を返す。サブクラスはこれをオーバーライドする必要がある
	virtual UScriptStruct* GetScriptStruct()const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FRPGGameplayEffectContext* Duplicate() const
	{
		FRPGGameplayEffectContext* NewContext = new FRPGGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	//特定のクラスまたは構造体のデータをシリアル化する方法を決定
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	//攻撃をブロックしたかどうかの判定
	UPROPERTY()
	bool bIsBlockedHit = false;

	//クリティカルしたかどうかの判定
	UPROPERTY()
	bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits<FRPGGameplayEffectContext> :public TStructOpsTypeTraitsBase2<FRPGGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};