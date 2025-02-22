// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Player/RPGPlayerController.h"
#include "RPGEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ARPGAIController;
/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGEnemy : public ARPGCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public: 
	ARPGEnemy();
	virtual void PossessedBy(AController* NewController)override;

	/** Enemy Interface */
	virtual void HighLightActor()override;
	virtual void UnHighLightActor()override;
	/** end Enemy Interface */

	/** Combat Interface  **/
	virtual int32 GetPlayerLevel()override;
	virtual void Die()override;
	/** end Combat Interface **/

	//敵の体力を引っ張ってくる
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag,int32 NewCount);

	UPROPERTY(BlueprintReadOnly,Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly,Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay()override;
	virtual void InitAbilityActorInfo()override;
	virtual void InitializeDefaultAttributes()const override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree>BehaviorTree;

	UPROPERTY()
	TObjectPtr<ARPGAIController>RPGAIController;
};
