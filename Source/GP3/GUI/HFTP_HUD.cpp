#include "HFTP_HUD.h"

#include "HFTP_MainMenu.h"
#include "HFTP_OptionsMenu.h"
#include "HFTP_PauseMenu.h"
#include "HFTP_CreditsMenu.h"
#include "HFTP_LoadingScreen.h"
#include "HFTP_TutorialMenu.h"
#include "HFTP_TutorialPromptHUD.h"
#include "HFTP_GameOverScreen.h"
#include "Blueprint/UserWidget.h"
#include "GP3/Systems/HFTP_GameInstance.h"
#include "GP3/Systems/HFTP_GameMode.h"
#include "GP3/Systems/HFTP_TutorialSystem.h"

void AHFTP_HUD::InitializeMenus()
{
	MainMenuWidgetRef->InitializeMenu();
	OptionsMenuWidgetRef->InitializeMenu();
	PauseMenuWidgetRef->InitializeMenu();
	CreditsMenuWidgetRef->InitializeMenu();
	TutorialMenuRef->InitializeMenu();
	TutorialPromptHUDRef->InitializeMenu();
	LoadingScreenRef->InitializeMenu();
	GameOverScreenWidgetRef->InitializeMenu();
}

void AHFTP_HUD::Initialize()
{
	CreateMenus();
	InitializeMenus();
}

void AHFTP_HUD::SetCurrentMenuState(EMenuState NewMenuState, EGameState PreviousState)
{
	if (CurrentMenuState == NewMenuState)
		return;

	if (CurrentMenu)
		CurrentMenu->EnableWidget(false);

	switch (NewMenuState)
	{
	case EMenuState::Options:
		CurrentMenu = OptionsMenuWidgetRef;
		OptionsMenuWidgetRef->PreviousState = PreviousState;
		break;
	case EMenuState::Pause:
		CurrentMenu = PauseMenuWidgetRef;
		PauseMenuWidgetRef->PreviousState = PreviousState;
		break;
	case EMenuState::TutorialMenu:
		CurrentMenu = TutorialMenuRef;
		TutorialMenuRef->PreviousState = PreviousState;
		UE_LOG(LogTemp, Log, TEXT("Tutorial Menu -> Previous State: %s"), *GetGameStateAsString(PreviousState));
		break;
	case EMenuState::LoadingScreen:
		CurrentMenu = LoadingScreenRef;
		LoadingScreenRef->PreviousState = PreviousState;
		break;
	case EMenuState::Credits:
		CurrentMenu = CreditsMenuWidgetRef;
		CreditsMenuWidgetRef->PreviousState = PreviousState;
		break;
	case EMenuState::InGame:
		{
			if (!Cast<UHFTP_GameInstance>(GetGameInstance())->HavePlayedTutorial())
			{
				CurrentMenu = TutorialPromptHUDRef;
				GameModeRef->GetTutorialSystem()->InitTutorialSystem(GameModeRef->GetTutorialDataAssets());
			}
			else
			{
				CurrentMenu = nullptr;
			}
		}
		break;
	case EMenuState::NoneMenu:
		CurrentMenu = nullptr;
		break;
	case EMenuState::GameOverScreen:
		CurrentMenu = GameOverScreenWidgetRef;
		GameOverScreenWidgetRef->PreviousState = PreviousState;
		GameOverScreenWidgetRef->OnGameOverScreen();
		break;
	default: break;
	}
	CurrentMenuState = NewMenuState;
	if (CurrentMenu)
		CurrentMenu->EnableWidget(true);
}

void AHFTP_HUD::SetSystemReferences(AHFTP_GameMode& GameMode, AHFTP_LevelManager* LevelManager) noexcept
{
	GameModeRef = &GameMode;
	LevelManagerRef = LevelManager;
}

void AHFTP_HUD::CreateMenus()
{
	checkf(MainMenuWidgetClass, TEXT("HFTP_HUD: Main Menu Widget Class is null"));
	checkf(OptionsMenuWidgetClass, TEXT("HFTP_HUD: Options Menu Widget Class is null"));
	checkf(PauseMenuWidgetClass, TEXT("HFTP_HUD: Pause Menu Widget Class is null"));
	checkf(CreditsMenuWidgetClass, TEXT("HFTP_HUD: Credits Menu Widget Class is null"));
	checkf(TutorialMenuClass, TEXT("HFTP_HUD: Tutorial Menu Class is null"));
	checkf(TutorialPromptHUDClass, TEXT("HFTP_HUD: Tutorial Prompt HUD Class is null"));
	checkf(LoadingScreenClass, TEXT("HFTP_HUD: Loading Screen Class is null"));
	checkf(GameOverScreenWidgetClass, TEXT("HFTP_HUD: Game Over Screen Widget Class is null"));

	MainMenuWidgetRef = CreateWidget<UHFTP_MainMenu>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidgetRef->SetSystemReferences(*GameModeRef);

	OptionsMenuWidgetRef = CreateWidget<UHFTP_OptionsMenu>(GetWorld(), OptionsMenuWidgetClass);
	OptionsMenuWidgetRef->SetSystemReferences(*GameModeRef);

	PauseMenuWidgetRef = CreateWidget<UHFTP_PauseMenu>(GetWorld(), PauseMenuWidgetClass);
	PauseMenuWidgetRef->SetSystemReferences(*GameModeRef);

	CreditsMenuWidgetRef = CreateWidget<UHFTP_CreditsMenu>(GetWorld(), CreditsMenuWidgetClass);
	CreditsMenuWidgetRef->SetSystemReferences(*GameModeRef);

	TutorialMenuRef = CreateWidget<UHFTP_TutorialMenu>(GetWorld(), TutorialMenuClass);
	TutorialMenuRef->SetSystemReferences(*GameModeRef);

	TutorialPromptHUDRef = CreateWidget<UHFTP_TutorialPromptHUD>(GetWorld(), TutorialPromptHUDClass);
	TutorialPromptHUDRef->SetSystemReferences(*GameModeRef);

	LoadingScreenRef = CreateWidget<UHFTP_LoadingScreen>(GetWorld(), LoadingScreenClass);
	LoadingScreenRef->SetSystemReferences(*GameModeRef);
	LoadingScreenRef->SetLevelManager(LevelManagerRef);

	GameOverScreenWidgetRef = CreateWidget<UHFTP_GameOverScreen>(GetWorld(), GameOverScreenWidgetClass);
	GameOverScreenWidgetRef->SetSystemReferences(*GameModeRef);
}


//UTILITY

FString AHFTP_HUD::GetMenuStateAsString(EMenuState MenuState) const noexcept
{
	switch (MenuState)
	{
	case EMenuState::Main: return "Main Menu";
	case EMenuState::Options: return "Options Menu";
	case EMenuState::Pause: return "Pause Menu";
	case EMenuState::TutorialMenu: return "Tutorial Menu";
	case EMenuState::LoadingScreen: return "Loading Screen";
	case EMenuState::Credits: return "Credits Menu";
	case EMenuState::InGame: return "In Game";
	case EMenuState::NoneMenu: return "None Menu";
	case EMenuState::HUDInit: return "HUD Init";
	case EMenuState::InGameMenu: return "In Game Menu";
	default: return "Unknown Menu State";
	}
}

FString AHFTP_HUD::GetGameStateAsString(EGameState GameState) const noexcept
{
	switch (GameState)
	{
	case EGameState::GameInit: return "Game Init";
	case EGameState::MainMenu: return "Main Menu";
	case EGameState::OptionsMenu: return "Options Menu";
	case EGameState::TutorialMenu: return "Tutorial Menu";
	case EGameState::LoadingScreen: return "Loading Screen";
	case EGameState::CreditsMenu: return "Credits Menu";
	case EGameState::StartPlaying: return "Start Playing";
	case EGameState::InGameBookMenu: return "In Game Book Menu";
	case EGameState::Playing: return "Playing";
	case EGameState::Pause: return "Pause";
	case EGameState::UnPause: return "UnPause";
	case EGameState::GameOver: return "Game Over";
	case EGameState::None: return "None";
	default: return "Unknown Game State";
	}
}
