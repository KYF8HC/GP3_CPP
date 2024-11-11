#include "HFTP_TutorialMenu.h"
#include "Components/Button.h"
#include "GP3/Systems/HFTP_GameMode.h"

void UHFTP_TutorialMenu::InitializeMenu()
{
	Super::InitializeMenu();
}

void UHFTP_TutorialMenu::AddListeners()
{
	Super::AddListeners();
	PlayButton->OnClicked.AddDynamic(this, &UHFTP_TutorialMenu::OnPlayButtonClicked);
}

void UHFTP_TutorialMenu::OnPlayButtonClicked()
{
	if (PreviousState != EGameState::Pause)
		GameModeRef->ChangeGameState(EGameState::StartPlaying, EGameState::TutorialMenu);
	else
		GameModeRef->ChangeGameState(EGameState::UnPause, EGameState::Pause);
}
