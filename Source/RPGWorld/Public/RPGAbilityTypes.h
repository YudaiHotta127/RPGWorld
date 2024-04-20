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

	//�V���A�����Ɏg�p�������ۂ̍\���̂�Ԃ��B�T�u�N���X�͂�����I�[�o�[���C�h����K�v������
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

	//����̃N���X�܂��͍\���̂̃f�[�^���V���A����������@������
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	//�U�����u���b�N�������ǂ����̔���
	UPROPERTY()
	bool bIsBlockedHit = false;

	//�N���e�B�J���������ǂ����̔���
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