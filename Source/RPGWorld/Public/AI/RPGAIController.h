// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RPGAIController.generated.h"

class UBlackBoardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGAIController : public AAIController
{
	GENERATED_BODY()
public:
	ARPGAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent>BehaviorTreeComponent;
};
