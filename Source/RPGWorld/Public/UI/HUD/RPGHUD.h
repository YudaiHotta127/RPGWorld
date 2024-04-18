// Copyright Yudai Hotta

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/RPGUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "RPGHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class URPGUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class RPGWORLD_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
public:
	//各ウィジェットによる画面をC++で作るたびにウィジェットコントローラーを作成する。

	//オーバーレイウィジェットを表示するためのWidgetControllerゲッターの作成
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	//ステータス画面を表示するためのWidgetControllerゲッターの作成
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:
	UPROPERTY()
	TObjectPtr<URPGUserWidget>OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget>OverlayWidgetClass;
	
	//オーバーレイウィジェットの作成するのに定義する

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>OverlayWidgetControllerClass;

	//End of OverlayWidget

	//ステータス画面を作成するのに定義する

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController>AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController>AttributeMenuWidgetControllerClass;
	//End Of AttributeMenuWidget
};
