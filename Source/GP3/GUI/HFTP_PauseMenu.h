#pragma once

#include "HFTP_MenuBase.h"
#include "HFTP_PauseMenu.generated.h"

class UButton;

UCLASS(Abstract)
class UHFTP_PauseMenu : public UHFTP_MenuBase
{
	GENERATED_BODY()
public:
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> ResumeButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> OptionsButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> TutorialButton{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> MainMenuButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget	))
	TObjectPtr<UButton> QuitButton{};

	
	UFUNCTION()
	void OnResumeButtonClick();

	UFUNCTION()
	void OnOptionsButtonClick();

	UFUNCTION()
	void OnTutorialButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();

	virtual void AddListeners() override;
};