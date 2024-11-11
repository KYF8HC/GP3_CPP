#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HFTP_TutorialDataAssets.generated.h"

UENUM()
enum class ETutorialType
{
	Move,
	Lean,
	Fireflies,
	PhotoFirst,
	Book,
	Compass,
	PhotoSecond,
	Sprint
};

UCLASS(BlueprintType)
class GP3_API UHFTP_TutorialDataAssets : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Tutorial")
	ETutorialType TutorialType{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Tutorial")
	FText TutorialDesc{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Tutorial")
	bool bIsFirst{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Tutorial")
	TObjectPtr<UHFTP_TutorialDataAssets> NextTutorial{};
};
