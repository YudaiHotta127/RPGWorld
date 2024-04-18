// Copyright Yudai Hotta


#include "AbilitySystem/Data/AttributeInfo.h"

	//DataAssetからRPGAttributeInfoの構造体を取得する
FRPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for (const FRPGAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	//配列内に何も見つからなかった場合にエラーメッセージを出力する
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FRPGAttributeInfo();
}
