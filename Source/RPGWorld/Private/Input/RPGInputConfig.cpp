// Copyright Yudai Hotta


#include "Input/RPGInputConfig.h"

const UInputAction* URPGInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FRPGInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag[%s],on InputConfig[%s]"),*InputTag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
}
