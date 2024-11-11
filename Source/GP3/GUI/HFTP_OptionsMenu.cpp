#include "HFTP_OptionsMenu.h"
#include "Components/Button.h"
#include "GP3/Systems/HFTP_GameMode.h"

void UHFTP_OptionsMenu::AddListeners()
{
	BackButton->OnClicked.AddDynamic(this, &UHFTP_OptionsMenu::OnBackButtonClick);
}

void UHFTP_OptionsMenu::OnBackButtonClick()
{
	GameModeRef->ChangeGameState(PreviousState, EGameState::OptionsMenu);
}
