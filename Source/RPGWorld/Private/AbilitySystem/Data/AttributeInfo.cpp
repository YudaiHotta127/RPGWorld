// Copyright Yudai Hotta


#include "AbilitySystem/Data/AttributeInfo.h"

	//DataAsset����RPGAttributeInfo�̍\���̂��擾����
FRPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for (const FRPGAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	//�z����ɉ���������Ȃ������ꍇ�ɃG���[���b�Z�[�W���o�͂���
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FRPGAttributeInfo();
}
