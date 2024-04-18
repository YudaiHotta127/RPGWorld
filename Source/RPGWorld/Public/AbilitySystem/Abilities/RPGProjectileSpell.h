// Copyright Yudai Hotta
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RPGDamageGameplayAbility.h"
#include "RPGProjectileSpell.generated.h"

class ARPGProjectile;
class UGameplayEffect;

/**
 * –‚–@‚Ì‹Ê‚ð‚Æ‚Î‚·
 */
UCLASS()
class RPGWORLD_API URPGProjectileSpell : public URPGDamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;

	UFUNCTION(BlueprintCallable,Category="Projectile")
	void SpawnProjectile(const FVector&ProjectileTargetLocation);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ARPGProjectile>ProjectileClass;


};
