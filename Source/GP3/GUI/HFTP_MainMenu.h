#pragma once

#include "HFTP_MenuBase.h"
#include "HFTP_MainMenu.generated.h"

class UButton;

UCLASS(Abstract)
class UHFTP_MainMenu : public UHFTP_MenuBase
{
	GENERATED_BODY()
public:

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> StartGameButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> OptionsButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> CreditsButton{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget	))
	TObjectPtr<UButton> QuitButton{};

	UFUNCTION()
	void OnStartGameButtonClick();

	UFUNCTION()
	void OnOptionsButtonClick();

	UFUNCTION()
	void OnCreditsButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();

	virtual void AddListeners() override;
};
