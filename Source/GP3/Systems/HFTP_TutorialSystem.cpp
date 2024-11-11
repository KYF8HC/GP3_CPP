#include "HFTP_TutorialSystem.h"

#include "HFTP_GameInstance.h"
#include "GP3/DataAssets/HFTP_TutorialDataAssets.h"

void UHFTP_TutorialSystem::InitTutorialSystem(const TArray<UHFTP_TutorialDataAssets*>& DataAssets)
{
	TutorialDataAssets = DataAssets;
	for (auto tutorial : TutorialDataAssets)
	{
		if(tutorial->bIsFirst)
		{
			CurrentTutorial = tutorial;
			UE_LOG(LogTemp, Log, TEXT("First tutorial found: %s"), *CurrentTutorial->TutorialDesc.ToString());
			break;
		}
	}
	
	OnInitTutorialPrompt.Broadcast(CurrentTutorial->TutorialDesc);
}

bool UHFTP_TutorialSystem::bIsTutorialActive(const ETutorialType Tutorial)
{
	if(CurrentTutorial)
		return CurrentTutorial->TutorialType == Tutorial;
	return false;
}

void UHFTP_TutorialSystem::CompleteTutorial(const ETutorialType Tutorial)
{
	if (!CurrentTutorial)
	{
		UE_LOG(LogTemp, Error, TEXT("No tutorial is active"));
		return;
	}
	if (CurrentTutorial->TutorialType == Tutorial)
	{
		CurrentTutorial = CurrentTutorial->NextTutorial;
		if (CurrentTutorial)
		{
			OnCompleteTutorial.Broadcast(CurrentTutorial->TutorialDesc);
		}
		else
		{
			OnLastTutorialComplete.Broadcast();
			Cast<UHFTP_GameInstance>(GetGameInstance())->SetHavePlayedTutorial();
			CurrentTutorial = nullptr;
		}
	}
}

