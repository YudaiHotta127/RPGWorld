// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FRPGAttributeInfo
{
	GENERATED_BODY()

	//���x���G�f�B�^��ł̉{���ҏW�̋֎~
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class RPGWORLD_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	//DataAsset����RPGAttributeInfo�̍\���̂��擾����
	FRPGAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false)const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FRPGAttributeInfo>AttributeInformation;
};
