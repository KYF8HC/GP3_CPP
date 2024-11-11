#pragma once

#include "CoreMinimal.h"
#include "HFTP_ObjectiveData.h"
#include "Components/ActorComponent.h"
#include "HFTP_ObjectiveInteractable.generated.h"

class UHFTP_ObjectiveSystem;

// This class is used for any interactable object that can be used to complete objectives
UCLASS(meta = (BlueprintSpawnableComponent))
class GP3_API UHFTP_ObjectiveInteractable : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void ActivateObjective();
	
	void CompleteObjective();
	
	FHFTP_ObjectiveData GetObjectiveData() const { return ObjectiveData; }


protected:
	
	UFUNCTION()
	void DeleteComponent(const FHFTP_ObjectiveData& ObjectiveDataToDelete);
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Objective", meta = (AllowPrivateAccess = "true"))
	FHFTP_ObjectiveData ObjectiveData{};
	
	TObjectPtr<UHFTP_ObjectiveSystem> ObjectiveSystemRef{};
};
