#include "HFTP_MenuBase.h"

void UHFTP_MenuBase::InitializeMenu()
{
	AddListeners();
}

void UHFTP_MenuBase::AddListeners()
{
}

void UHFTP_MenuBase::EnableWidget(bool bEnable)
{
	if (bEnable)
	{
		AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("%s added to viewport"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s removed from viewport"), *GetName());
		RemoveFromParent();
	}
}

void UHFTP_MenuBase::SetSystemReferences(AHFTP_GameMode& GameMode) noexcept
{
	GameModeRef = &GameMode;
}
