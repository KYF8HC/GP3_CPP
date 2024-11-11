#pragma once

#include "CoreMinimal.h"
#include "HFTP_MenuBase.h"
#include "HFTP_TutorialPromptHUD.generated.h"

class UHFTP_TutorialSystem;
class UImage;
class UTextBlock;

UCLASS(Abstract)
class GP3_API UHFTP_TutorialPromptHUD : public UHFTP_MenuBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> TutorialText{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UImage> CheckmarkImage{};

	UPROPERTY()
	TObjectPtr<UHFTP_TutorialSystem> TutorialSystemRef{};
	
	

public:
	virtual void InitializeMenu() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void InitTutorialText(const FText& NewText);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnim(const FText& NewText);

	UFUNCTION()
	void CloseMenu();
};
