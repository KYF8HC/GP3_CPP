#include "HFTP_PauseMenu.h"
#include "Components/Button.h"
#include "GP3/Systems/HFTP_GameMode.h"


void UHFTP_PauseMenu::OnResumeButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::UnPause);
}

void UHFTP_PauseMenu::OnOptionsButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::OptionsMenu, EGameState::Pause);
}

void UHFTP_PauseMenu::OnTutorialButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::TutorialMenu, EGameState::Pause);
}

void UHFTP_PauseMenu::OnMainMenuButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::MainMenu);
}

void UHFTP_PauseMenu::OnQuitButtonClick()
{
	GameModeRef->QuitGame();
}

void UHFTP_PauseMenu::AddListeners()
{
	ResumeButton->OnClicked.AddDynamic(this, &UHFTP_PauseMenu::OnResumeButtonClick);
	OptionsButton->OnClicked.AddDynamic(this, &UHFTP_PauseMenu::OnOptionsButtonClick);
	TutorialButton->OnClicked.AddDynamic(this, &UHFTP_PauseMenu::OnTutorialButtonClick);
	MainMenuButton->OnClicked.AddDynamic(this, &UHFTP_PauseMenu::OnMainMenuButtonClick);
	QuitButton->OnClicked.AddDynamic(this, &UHFTP_PauseMenu::OnQuitButtonClick);
}
