#pragma once

#include "CoreMinimal.h"
#include "HFTP_MenuBase.h"
#include "HFTP_GameOverScreen.generated.h"

UCLASS()
class GP3_API UHFTP_GameOverScreen : public UHFTP_MenuBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnGameOverScreen();
};
