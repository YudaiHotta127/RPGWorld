// Copyright Yudai Hotta


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
//ここの処理はステータスをステータス画面に反映

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	URPGAttributeSet* AS = CastChecked<URPGAttributeSet>(AttributeSet);

	//属性が変更されるたびに属性の変更に応じてラムダが呼び出される
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

//初期値をブロードキャストする前に情報デリゲートを作成しておく
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
