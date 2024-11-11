#pragma once

#include "HFTP_MenuBase.h"
#include "HFTP_OptionsMenu.generated.h"

class UButton;

UCLASS(Abstract)
class UHFTP_OptionsMenu : public UHFTP_MenuBase
{
	GENERATED_BODY()
public:
	virtual void AddListeners() override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons", meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> BackButton{};

	UFUNCTION()
	void OnBackButtonClick();
};
