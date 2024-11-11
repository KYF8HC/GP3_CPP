#include "HFTP_TutorialPromptHUD.h"

#include "GP3/Systems/HFTP_GameMode.h"
#include "GP3/Systems/HFTP_TutorialSystem.h"

void UHFTP_TutorialPromptHUD::InitializeMenu()
{
	Super::InitializeMenu();
	TutorialSystemRef = GameModeRef->GetTutorialSystem();
	
	TutorialSystemRef->OnInitTutorialPrompt.AddDynamic(this, &UHFTP_TutorialPromptHUD::InitTutorialText);
	TutorialSystemRef->OnCompleteTutorial.AddDynamic(this, &UHFTP_TutorialPromptHUD::PlayAnim);
	TutorialSystemRef->OnLastTutorialComplete.AddDynamic(this, &UHFTP_TutorialPromptHUD::CloseMenu);
}

void UHFTP_TutorialPromptHUD::CloseMenu()
{
	TutorialSystemRef->OnInitTutorialPrompt.RemoveDynamic(this, &UHFTP_TutorialPromptHUD::InitTutorialText);
	TutorialSystemRef->OnCompleteTutorial.RemoveDynamic(this, &UHFTP_TutorialPromptHUD::PlayAnim);
	TutorialSystemRef->OnLastTutorialComplete.RemoveDynamic(this, &UHFTP_TutorialPromptHUD::CloseMenu);

	RemoveFromParent();
}
