// Copyright Yudai Hotta


#include "Player/RPGPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "RPGGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/RPGInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

ARPGPlayerController::ARPGPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

//�_���[�W�\���������T�[�o�[��ŌĂяo����
void ARPGPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter)&&DamageTextComponentClass)
	{
		//�E�B�W�F�b�g�R���|�[�l���g�𓮓I�ɍ쐬
		UDamageTextComponent*DamageText=NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		//�^�[�Q�b�g�L�����N�^�[��RootComponent�ɃA�^�b�`(�A�^�b�`���闝�R�̓_���[�W���󂯂��L�����N�^�[�̈ʒu����\�������邽��)
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		//�����ɐ؂藣���Ă��̏�ɕ\��������
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		DamageText->SetDamageText(DamageAmount,bBlockedHit,bCriticalHit);
	}
}

void ARPGPlayerController::AutoRun()
{
	if (!bAutoRunning)return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void ARPGPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor)LastActor->UnHighLightActor();
		if (ThisActor)ThisActor->HighLightActor();
	}

}

void ARPGPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor  ? true : false;
		bAutoRunning = false;
	}
}

void ARPGPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())	GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if (GetASC())	GetASC()->AbilityInputTagReleased(InputTag);

	if (!bTargeting&&!bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ARPGPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())			GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if (bTargeting||bShiftKeyDown)
	{
		if (GetASC())			GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit)			CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

URPGAbilitySystemComponent* ARPGPlayerController::GetASC()
{
	if (RPGAbilitySystemComponent == nullptr)
	{
		RPGAbilitySystemComponent =Cast<URPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return RPGAbilitySystemComponent;
}


void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(RPGContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) 
	{
		Subsystem->AddMappingContext(RPGContext, 0);
	}
	//�}�E�X�̕\��
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	URPGInputComponent* RPGInputComponent = CastChecked<URPGInputComponent>(InputComponent);

	RPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::Move);
	RPGInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ARPGPlayerController::ShiftPressed);
	RPGInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ARPGPlayerController::ShiftReleased);
	RPGInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ARPGPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}
