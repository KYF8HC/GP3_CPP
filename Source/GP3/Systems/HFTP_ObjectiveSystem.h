#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HFTP_ObjectiveData.h"
#include "HFTP_ObjectiveSystem.generated.h"

class UHFTP_MenuBase;
class UHFTP_ObjectiveDataAsset;

DECLARE_MULTICAST_DELEGATE(FUpdateObjectiveList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuccessfullyCompletedObjective, const FHFTP_ObjectiveData&, ObjectiveData);
DECLARE_MULTICAST_DELEGATE(FOnLastObjectiveCompleted);
UCLASS()
class UHFTP_ObjectiveSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	///////////////
	// FUNCTIONS //
	///////////////

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable)
	void AddObjective(AActor* InteractableActor, const FHFTP_ObjectiveData& ObjectiveData);

	UFUNCTION(BlueprintCallable)
	void ActivateObjective(AActor* Key, const FHFTP_ObjectiveData& ObjectiveData);

	UFUNCTION(BlueprintCallable)
	void CompleteObjective(const FHFTP_ObjectiveData& ObjectiveData);

	UFUNCTION(BlueprintCallable)
	AActor* GetInteractableActor(const FHFTP_ObjectiveData& ObjectiveData) const;

	UFUNCTION()
	void RestartGame();

	TArray<FHFTP_ObjectiveData>& GetActiveObjectives() noexcept { return ActiveObjectives; }

	FUpdateObjectiveList OnUpdateObjectiveList;
	FOnRestartGame OnRestartGame;
	FSuccessfullyCompletedObjective OnSuccessfullyCompletedObjective;
	FOnLastObjectiveCompleted OnLastObjectiveCompleted;
	
private:

	////////////////
	// REFERENCES //
	////////////////
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_MenuBase> ObjectiveCompletedMenuClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_MenuBase> ActiveObjectivesMenuListClass{};


	///////////////
	// VARIABLES //
	///////////////
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TMap<AActor*, FHFTP_ObjectiveData> AllObjectives{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TArray<FHFTP_ObjectiveData> ActiveObjectives{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	TArray<FHFTP_ObjectiveData> CompletedObjectives{};
};
