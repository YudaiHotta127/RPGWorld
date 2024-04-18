// Copyright Yudai Hotta


#include "RPGAssetManager.h"
#include "RPGGameplayTags.h"
#include "AbilitySystemGlobals.h"

//ƒGƒ“ƒWƒ“‚ÌAssetManager‚ðŽæ“¾‚·‚é
URPGAssetManager& URPGAssetManager::Get()
{
	check(GEngine);
	URPGAssetManager* RPGAssetManager = Cast<URPGAssetManager>(GEngine->AssetManager);
	return *RPGAssetManager;
}

void URPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FRPGGameplayTags::InitializeNativeGameplayTag();

	//This is required to use Target Data
	UAbilitySystemGlobals::Get().InitGlobalData();
}
