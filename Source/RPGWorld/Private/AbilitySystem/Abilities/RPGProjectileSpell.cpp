// Copyright Yudai Hotta


#include "AbilitySystem/Abilities/RPGProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/RPGProjectile.h"
#include "Interaction/CombatInterface.h"
#include "RPGGameplayTags.h"

void URPGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);


}

void URPGProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{

	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		//SpawnActor���g�p���Ȃ����R�̓X�|�[�����I���O�ɁA���˕��̃_���[�W�ɑ΂���GameplayAbility�̎d�l��ݒ肵��������
		ARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARPGProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent*SourceASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>>Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);

		const FGameplayEffectSpecHandle SpecHandle=SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(), EffectContextHandle);
		
		//GameEffect���ł͂Ȃ��ACpp������_���[�W�ʂ̎w����s��
		const FRPGGameplayTags GameplayTags = FRPGGameplayTags::Get();
		
		for (auto& Pair: DamageTypes)
		{
			//CurveTable���烌�x���ɉ����ăX�P�[�����O���ꂽfloat�l���Ƃ��Ă���
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			//Damage�^�O�փ_���[�W�̒l��ݒ肷��
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
		}

		//GameplayEffectSpec�ւ̓K�p
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
