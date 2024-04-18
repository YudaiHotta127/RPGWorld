// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "RPGProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class RPGWORLD_API ARPGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ARPGProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>ProjectileMovement;

	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed()override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OhterActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;

	bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem>ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent>LoopingSoundComponent;
};
