// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>CharacterClassInfo;
};
