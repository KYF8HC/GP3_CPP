#include "HFTP_MainMenu.h"

#include "Components/Button.h"
#include "GP3/Systems/HFTP_GameMode.h"


void UHFTP_MainMenu::OnStartGameButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::LoadingScreen, EGameState::MainMenu);
}

void UHFTP_MainMenu::OnOptionsButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::OptionsMenu, EGameState::MainMenu);
}

void UHFTP_MainMenu::OnCreditsButtonClick()
{
	GameModeRef->ChangeGameState(EGameState::CreditsMenu, EGameState::MainMenu);
}

void UHFTP_MainMenu::OnQuitButtonClick()
{
	GameModeRef->QuitGame();
}

void UHFTP_MainMenu::AddListeners()
{
	StartGameButton->OnClicked.AddDynamic(this, &UHFTP_MainMenu::OnStartGameButtonClick);
	OptionsButton->OnClicked.AddDynamic(this, &UHFTP_MainMenu::OnOptionsButtonClick);
	CreditsButton->OnClicked.AddDynamic(this, &UHFTP_MainMenu::OnCreditsButtonClick);
	QuitButton->OnClicked.AddDynamic(this, &UHFTP_MainMenu::OnQuitButtonClick);
}
