// Copyright Yudai Hotta


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
//�����̏����̓X�e�[�^�X���X�e�[�^�X��ʂɔ��f

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	URPGAttributeSet* AS = CastChecked<URPGAttributeSet>(AttributeSet);

	//�������ύX����邽�тɑ����̕ύX�ɉ����ă����_���Ăяo�����
	for (auto& Pair : AS->TagsToAttributes) 
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData&Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

//�����l���u���[�h�L���X�g����O�ɏ��f���Q�[�g���쐬���Ă���
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	URPGAttributeSet*AS= CastChecked<URPGAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto&Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute)const
{

		FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
		Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
		AttributeInfoDelegate.Broadcast(Info);

}
