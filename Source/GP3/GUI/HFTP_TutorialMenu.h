#pragma once

#include "CoreMinimal.h"
#include "HFTP_MenuBase.h"
#include "HFTP_TutorialMenu.generated.h"


class UButton;

UCLASS(Abstract)
class GP3_API UHFTP_TutorialMenu : public UHFTP_MenuBase
{
	GENERATED_BODY()

public:
	virtual void InitializeMenu() override;
	virtual void AddListeners() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TutorialMenu",
		meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UButton> PlayButton{};

	UFUNCTION()
	void OnPlayButtonClicked();
};
