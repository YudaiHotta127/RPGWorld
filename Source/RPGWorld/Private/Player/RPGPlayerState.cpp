// Copyright Yudai Hotta


#include "Player/RPGPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"

ARPGPlayerState::ARPGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");

	//�l�b�g�X�V�p�x
	//�N���C�A���g���1�b������100��X�V�����
	NetUpdateFrequency = 100.f;
}

void ARPGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARPGPlayerState, Level);
}

UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
