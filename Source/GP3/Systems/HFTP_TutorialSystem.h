#pragma once

#include "CoreMinimal.h"
#include "GP3/DataAssets/HFTP_TutorialDataAssets.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HFTP_TutorialSystem.generated.h"

enum class ETutorialType;
class UHFTP_TutorialDataAssets;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitTutorialPrompt, const FText&, TutorialText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteTutorial, const FText&, TutorialText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLastTutorialComplete);


UCLASS()
class GP3_API UHFTP_TutorialSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UHFTP_TutorialDataAssets>> TutorialDataAssets{};

	UPROPERTY()
	TObjectPtr<UHFTP_TutorialDataAssets> CurrentTutorial{};

public:
	UFUNCTION()
	void InitTutorialSystem(const TArray<UHFTP_TutorialDataAssets*>& DataAssets);

	bool bIsTutorialActive(const ETutorialType Tutorial);

	void CompleteTutorial(const ETutorialType Tutorial);

	FOnInitTutorialPrompt OnInitTutorialPrompt;
	FOnCompleteTutorial OnCompleteTutorial;
	FOnLastTutorialComplete OnLastTutorialComplete;
};
