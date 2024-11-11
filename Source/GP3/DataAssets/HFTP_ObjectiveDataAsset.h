#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HFTP_ObjectiveDataAsset.generated.h"

UENUM()
enum class EObjectiveType : uint8
{
	Photo UMETA(DisplayName = "Photo"),
	Explore UMETA(DisplayName = "Explore"),
};

UCLASS(BlueprintType)
class GP3_API UHFTP_ObjectiveDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UHFTP_ObjectiveDataAsset();
	
	const FGuid& GetObjectiveID() const noexcept { return ObjectiveID; }
	const FText& GetObjectiveTitle() const noexcept { return ObjectiveTitle; }
	const FText& GetObjectiveDescription() const noexcept { return ObjectiveDescription; }
	bool IsFirstObjective() const noexcept { return bIsFirstObjective; }
	bool IsLastObjective() const noexcept { return bIsLastObjective; }
	EObjectiveType GetObjectiveType() const noexcept { return Type; }
	TSoftObjectPtr<UHFTP_ObjectiveDataAsset> GetUnlockObjective() const noexcept { return UnlockObjective; }


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective")
	uint8 PageIndex{};
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	FGuid ObjectiveID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	FText ObjectiveTitle{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	FText ObjectiveDescription{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	bool bIsFirstObjective{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	bool bIsLastObjective{false};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	EObjectiveType Type{};

	/// <summary>
	/// A list of objectives that will be unlocked when this objective is completed
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UHFTP_ObjectiveDataAsset> UnlockObjective{};
};
