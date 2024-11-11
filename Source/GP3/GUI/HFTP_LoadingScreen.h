#pragma once

#include "CoreMinimal.h"
#include "HFTP_MenuBase.h"
#include "HFTP_LoadingScreen.generated.h"

class AHFTP_LevelManager;

UCLASS()
class GP3_API UHFTP_LoadingScreen : public UHFTP_MenuBase
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loading Screen", meta = (AllowPrivateAccess = "true"))
	TArray<FText> Tips;

	UPROPERTY(BlueprintReadOnly, Category = "Loading Screen", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_LevelManager> LevelManagerRef{};

public:
	void SetLevelManager(AHFTP_LevelManager* LevelManager) { LevelManagerRef = LevelManager; }
};
