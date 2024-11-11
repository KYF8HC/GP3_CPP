#pragma once

#include "CoreMinimal.h"
#include "GP3/DataAssets/HFTP_ObjectiveDataAsset.h"
#include "HFTP_ObjectiveData.generated.h"


class UHFTP_ObjectiveDataAsset;

USTRUCT(BlueprintType)
struct FHFTP_ObjectiveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Objective")
	TObjectPtr<UHFTP_ObjectiveDataAsset> ObjectiveDataAsset{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective")
	bool bIsActive{false};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective")
	bool bIsCompleted{false};

	bool operator==(const FHFTP_ObjectiveData& Other) const
	{
		return ObjectiveDataAsset->GetObjectiveID() == Other.ObjectiveDataAsset->GetObjectiveID();
	}
	
	bool IsValid() const
	{
		if (!ObjectiveDataAsset)
		{
			return false;
		}
		return true;
	}
};
