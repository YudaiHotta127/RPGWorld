// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacterBase.h"
#include "RPGCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()
public:
	ARPGCharacter();
	virtual void PossessedBy(AController* NewController)override;
	virtual void OnRep_PlayerState()override;

	/** Combat Interface  **/
	virtual int32 GetPlayerLevel()override;
	/** end Combat Interface **/

private:
	virtual void InitAbilityActorInfo()override;
};
