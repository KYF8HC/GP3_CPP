#include "HFTP_BookMenuBase.h"


void UHFTP_BookMenuBase::InitializeMenu()
{
	AddListeners();
}

void UHFTP_BookMenuBase::AddListeners()
{
}

void UHFTP_BookMenuBase::SetSystemReferences(AHFTP_GameMode& GameMode) noexcept
{
	GameModeRef = &GameMode;
}

void UHFTP_BookMenuBase::Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex)
{
	Super::Init(InBookMenuActor, InPageSectionIndex, InPageIndex);
	
}