#include "HFTP_ObjectiveSystem.h"

void UHFTP_ObjectiveSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("UHFTP_ObjectiveSystem: Initialized"));
}

void UHFTP_ObjectiveSystem::Deinitialize()
{
	OnUpdateObjectiveList.Clear();
	OnSuccessfullyCompletedObjective.Clear();

	Super::Deinitialize();
}

void UHFTP_ObjectiveSystem::AddObjective(AActor* InteractableActor, const FHFTP_ObjectiveData& ObjectiveData)
{
	if (!AllObjectives.Contains(InteractableActor))
	{
		UE_LOG(LogTemp, Log, TEXT("UHFTP_ObjectiveSystem: Adding objective"));
		AllObjectives.Add(InteractableActor, ObjectiveData);
		if (ObjectiveData.ObjectiveDataAsset->IsFirstObjective())
			ActivateObjective(InteractableActor, ObjectiveData);
	}
	else
	{
		UE_LOG(LogTemp, Warning,
		       TEXT("UHFTP_ObjectiveSystem: You are trying to add an objective that already exists"));
	}
}

void UHFTP_ObjectiveSystem::ActivateObjective(AActor* Key, const FHFTP_ObjectiveData& ObjectiveData)
{
	if (AllObjectives.Contains(Key) && !ActiveObjectives.Contains(ObjectiveData))
	{
		UE_LOG(LogTemp, Log, TEXT("UHFTP_ObjectiveSystem: Activating objective %s"),
		       *ObjectiveData.ObjectiveDataAsset->GetObjectiveTitle().ToString());
		ActiveObjectives.Add(ObjectiveData);
		OnUpdateObjectiveList.Broadcast();
	}
	else
		UE_LOG(LogTemp, Warning,
	       TEXT("UHFTP_ObjectiveSystem: You are trying to activate an objective that does not exist"));
}

void UHFTP_ObjectiveSystem::CompleteObjective(const FHFTP_ObjectiveData& ObjectiveData)
{
	if (ActiveObjectives.Contains(ObjectiveData) && !CompletedObjectives.Contains(ObjectiveData))
	{
		ActiveObjectives.Remove(ObjectiveData);
		CompletedObjectives.Add(ObjectiveData);
		OnUpdateObjectiveList.Broadcast();
		OnSuccessfullyCompletedObjective.Broadcast(ObjectiveData);

		if (!ObjectiveData.ObjectiveDataAsset->GetUnlockObjective())
		{
			if (ObjectiveData.ObjectiveDataAsset->IsLastObjective())
			{
				OnLastObjectiveCompleted.Broadcast();
				return;
			}
			return;
		}

		for (auto Objective : AllObjectives)
		{
			if (Objective.Value.ObjectiveDataAsset->GetObjectiveID() ==
				ObjectiveData.ObjectiveDataAsset->GetUnlockObjective()->GetObjectiveID())
			{
				ActivateObjective(Objective.Key, Objective.Value);
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning,
	       TEXT("UHFTP_ObjectiveSystem: You are trying to complete an objective that is not active"));
}

AActor* UHFTP_ObjectiveSystem::GetInteractableActor(const FHFTP_ObjectiveData& ObjectiveData) const
{
	if (AActor* const* FoundActor = AllObjectives.FindKey(ObjectiveData))
	{
		return *FoundActor; // Dereference the pointer to get AActor*
	}
	return nullptr;
}

void UHFTP_ObjectiveSystem::RestartGame()
{
	AllObjectives.Empty();
	ActiveObjectives.Empty();
	CompletedObjectives.Empty();
	OnRestartGame.Broadcast();
}
