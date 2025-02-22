// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "RPGPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class URPGInputConfig;
class URPGAbilitySystemComponent;
class USplineComponent;
class UDamageTextComponent;
/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARPGPlayerController();
	virtual void PlayerTick(float DeltaTime)override;

	//生成するWidgetComponentにダメージを渡す
	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(float DamageAmount,ACharacter*TargetCharacter, bool bBlockedHit, bool bCriticalHit);

protected:
	virtual void BeginPlay()override;
	virtual void SetupInputComponent()override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext>RPGContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction>MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction>ShiftAction;

	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;

	void Move(const  FInputActionValue& InputActionValue);

	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	FHitResult CursorHit;

	//Click Moveで使用する
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<URPGInputConfig>InputConfig;


	UPROPERTY()
	TObjectPtr<URPGAbilitySystemComponent>RPGAbilitySystemComponent;

	URPGAbilitySystemComponent* GetASC();

	FVector CachedDestination=FVector::ZeroVector;
	float FollowTime=0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius=50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>Spline;

	void AutoRun();
	//Click Move End

	//BP_RPGPlayerControllerにBP_DamageTextComponentを設定するのを忘れない
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent>DamageTextComponentClass;
};

