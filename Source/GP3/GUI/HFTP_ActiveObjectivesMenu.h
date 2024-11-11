#pragma once

#include "CoreMinimal.h"
#include "HFTP_MenuBase.h"
#include "HFTP_ActiveObjectivesMenu.generated.h"

class UHFTP_ObjectiveSystem;
class UVerticalBox;

UCLASS(Abstract)
class UHFTP_ActiveObjectivesMenu : public UHFTP_MenuBase
{
	GENERATED_BODY()

public:
	void SetObjectiveSystemRef(UHFTP_ObjectiveSystem& ObjectiveSystem) noexcept
	{
		ObjectiveSystemRef = ObjectiveSystem;
	}

	void InitializeMenu() override;

	UFUNCTION()
	void UpdateMenu();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Objective List",
		meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UVerticalBox> ObjectiveList{};

private:
	TObjectPtr<UHFTP_ObjectiveSystem> ObjectiveSystemRef{};
};
