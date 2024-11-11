#include "HFTP_CreditsMenu.h"

#include "Components/Button.h"
#include "GP3/Systems/HFTP_GameMode.h"

void UHFTP_CreditsMenu::AddListeners()
{
	BackButton->OnClicked.AddDynamic(this, &UHFTP_CreditsMenu::OnBackButtonClick);
}

void UHFTP_CreditsMenu::OnBackButtonClick()
{
	GameModeRef->ChangeGameState(PreviousState, EGameState::CreditsMenu);
}
