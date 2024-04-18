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
	//�e�E�B�W�F�b�g�ɂ���ʂ�C++�ō�邽�тɃE�B�W�F�b�g�R���g���[���[���쐬����B

	//�I�[�o�[���C�E�B�W�F�b�g��\�����邽�߂�WidgetController�Q�b�^�[�̍쐬
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	//�X�e�[�^�X��ʂ�\�����邽�߂�WidgetController�Q�b�^�[�̍쐬
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:
	UPROPERTY()
	TObjectPtr<URPGUserWidget>OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget>OverlayWidgetClass;
	
	//�I�[�o�[���C�E�B�W�F�b�g�̍쐬����̂ɒ�`����

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>OverlayWidgetControllerClass;

	//End of OverlayWidget

	//�X�e�[�^�X��ʂ��쐬����̂ɒ�`����

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController>AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController>AttributeMenuWidgetControllerClass;
	//End Of AttributeMenuWidget
};
