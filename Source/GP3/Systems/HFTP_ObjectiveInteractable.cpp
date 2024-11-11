#include "HFTP_ObjectiveInteractable.h"
#include "HFTP_ObjectiveSystem.h"

void UHFTP_ObjectiveInteractable::ActivateObjective()
{
	if (ObjectiveData.ObjectiveDataAsset)
		ObjectiveSystemRef->ActivateObjective(GetOwner(), ObjectiveData);
	else
		UE_LOG(LogTemp, Error, TEXT("HFTP_ObjectiveInteractable: ObjectiveData is nullptr in %s"), *GetOwner()->GetName());
}

void UHFTP_ObjectiveInteractable::CompleteObjective()
{
	if (ObjectiveData.ObjectiveDataAsset)
	{
		ObjectiveSystemRef->CompleteObjective(ObjectiveData);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("HFTP_ObjectiveInteractable: ObjectiveData is nullptr in %s"), *GetOwner()->GetName());
}


void UHFTP_ObjectiveInteractable::DeleteComponent(const FHFTP_ObjectiveData& ObjectiveDataToDelete)
{
	UE_LOG(LogTemp, Log, TEXT("HFTP_ObjectiveInteractable: Deleting component"));
}

void UHFTP_ObjectiveInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	ObjectiveSystemRef = GetOwner()->GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	if (!ObjectiveSystemRef)
	{
		UE_LOG(LogTemp, Error, TEXT("HFTP_ObjectiveInteractable: ObjectiveSystemRef is nullptr in %s"), *GetOwner()->GetName());
		return;
	}
	if (ObjectiveData.ObjectiveDataAsset)
	{
		ObjectiveSystemRef->AddObjective(GetOwner(), ObjectiveData);
		ObjectiveSystemRef->OnSuccessfullyCompletedObjective.AddDynamic(
			this, &UHFTP_ObjectiveInteractable::DeleteComponent);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("HFTP_ObjectiveInteractable: ObjectiveData is nullptr in %s"), *GetOwner()->GetName());
}
