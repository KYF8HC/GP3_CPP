#include "HFTP_GameMode.h"
#include "HFTP_GameInstance.h"
#include "HFTP_LevelManager.h"
#include "HFTP_Player.h"
#include "HFTP_PlayerController.h"
#include "HFTP_SoundManager.h"
#include "HFTP_TutorialSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GP3/GUI/HFTP_HUD.h"
#include "Kismet/GameplayStatics.h"

AHFTP_GameMode::AHFTP_GameMode() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHFTP_GameMode::SetChromaticAberration(bool bShouldEnable) noexcept
{
	bChromaticAberrationBeEnabled = bShouldEnable;
	OnChromaticAberrationChanged.Broadcast(bShouldEnable);
}

void AHFTP_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	CreateSystems();

	const UHFTP_GameInstance* GameInstanceRef = Cast<UHFTP_GameInstance>(GetGameInstance());
	bShouldFlashlightBeEnabled = GameInstanceRef->IsFlashingLightsEnabled();
	bChromaticAberrationBeEnabled = GameInstanceRef->IsChromaticAberrationEnabled();
}

void AHFTP_GameMode::StartPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AHFTP_GameMode::StartPlay"));
	SaveReferences();
	InjectReferences();
	HUDRef->Initialize();
	PlayerControllerRef->SetInputModeToUIOnly();
	ChangeGameState(EGameState::LoadingScreen, EGameState::MainMenu);
	Super::StartPlay();
}

void AHFTP_GameMode::CreateSystems()
{
	//SoundManager
	SoundManagerRef = GetGameInstance()->GetSubsystem<UHFTP_SoundManager>();
	if (!SoundManagerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Sound Manager failed to load"));
	}
	else
	{
		SoundManagerRef->LoadSounds(SoundDataAsset);
	}

	//TutorialSystem
	TutorialSystemRef = GetGameInstance()->GetSubsystem<UHFTP_TutorialSystem>();
	if (!TutorialSystemRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Tutorial System failed to load"));
	}

	//ObjectiveSystem
	ObjectiveSystemRef = GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	if (!ObjectiveSystemRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Objective System failed to load"));
	}
	else
	{
		ObjectiveSystemRef->OnLastObjectiveCompleted.AddUObject(this, &AHFTP_GameMode::GameOver);
	}
	
	//LevelManager
	if (LevelManagerClassRef)
	{
		LevelManagerRef = GetWorld()->SpawnActor<AHFTP_LevelManager>(LevelManagerClassRef);
		if (!LevelManagerRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level Manager failed to spawn"));
		}
		else
		{
			LevelManagerRef->SetLevels(GameLevelNames);
			LevelManagerRef->OnAllLevelsLoaded.AddUObject(this, &AHFTP_GameMode::StartGame);
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Level Manager class reference is null"));
}

void AHFTP_GameMode::SetupPlayer()
{
	PlayerRef->GetCharacterMovement()->GravityScale = 0.0f;
	PlayerRef->SetGameModeRef(this);
	PlayerRef->SetPlayerControllerRef(PlayerControllerRef);
	PlayerRef->SetTutorialSystemRef(TutorialSystemRef);

	PlayerStartLocation = PlayerRef->GetActorLocation();
}

void AHFTP_GameMode::SaveReferences()
{
	PlayerRef = Cast<AHFTP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(PlayerRef, TEXT("AHFTP_GameMode::SaveReferences: Player is not valid"));

	PlayerControllerRef = Cast<AHFTP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerControllerRef, TEXT("AHFTP_GameMode::SaveReferences: PlayerController is not valid"));

	HUDRef = Cast<AHFTP_HUD>(PlayerControllerRef->GetHUD());
	checkf(HUDRef, TEXT("AHFTP_GameMode::SaveReferences: HUD is not valid"));

	SetupPlayer();
}

void AHFTP_GameMode::InjectReferences()
{
	HUDRef->SetSystemReferences(*this, LevelManagerRef);
}

void AHFTP_GameMode::StartGame()
{
	checkf(PlayerRef, TEXT("AHFTP_GameMode::StartGame: Player is not valid"));
	checkf(LevelManagerRef, TEXT("AHFTP_GameMode::StartGame: LevelManager is not valid"));
	checkf(PlayerControllerRef, TEXT("AHFTP_GameMode::StartGame: PlayerController is not valid"));
	checkf(HUDRef, TEXT("AHFTP_GameMode::StartGame: HUD is not valid"));

	
	PlayerRef->ResumePlaying();
	PlayerControllerRef->SetInputModeToGameOnly();
	PlayerControllerRef->SetPause(false);
	HUDRef->SetCurrentMenuState(EMenuState::InGame, EGameState::None);
	ChangeGameState(EGameState::Playing);
}

void AHFTP_GameMode::PauseGame()
{
	UE_LOG(LogTemp, Log, TEXT("Game Paused"));
	PlayerControllerRef->SetPause(true);
	PlayerControllerRef->SetInputModeToUIOnly();
	HUDRef->SetCurrentMenuState(EMenuState::Pause, EGameState::None);
}

void AHFTP_GameMode::UnPauseGame()
{
	PlayerControllerRef->SetPause(false);
	PlayerControllerRef->SetInputModeToGameOnly();
	HUDRef->SetCurrentMenuState(EMenuState::InGame, EGameState::None);
	ChangeGameState(EGameState::Playing);
}

void AHFTP_GameMode::UnLoadAllLevels()
{
	LevelManagerRef->UnloadCurrentLevel(GameLevelNames);
	GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>()->RestartGame();
	PlayerControllerRef->SetPause(false);
	PlayerRef->HideUI();
}

void AHFTP_GameMode::GameOver()
{
	ChangeGameState(EGameState::GameOver);
}

void AHFTP_GameMode::QuitGame()
{
	//Close the game
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerControllerRef, EQuitPreference::Quit, false);
}

void AHFTP_GameMode::SetMainMenuState(EGameState PreviousState)
{
	PlayerControllerRef->SetInputModeToUIOnly();
	UnLoadAllLevels();
}

void AHFTP_GameMode::ChangeGameState(EGameState NewGameState, EGameState PreviousState)
{
	if (CurrentGameState == NewGameState)
		return;

	CurrentGameState = NewGameState;
	switch (NewGameState)
	{
	case EGameState::MainMenu:
		SetMainMenuState(PreviousState);
		break;
	case EGameState::OptionsMenu:
		HUDRef->SetCurrentMenuState(EMenuState::Options, PreviousState);
		break;
	case EGameState::CreditsMenu:
		HUDRef->SetCurrentMenuState(EMenuState::Credits, PreviousState);
		break;
	case EGameState::LoadingScreen:
		HUDRef->SetCurrentMenuState(EMenuState::LoadingScreen, PreviousState);
		break;
	case EGameState::TutorialMenu:
		HUDRef->SetCurrentMenuState(EMenuState::TutorialMenu, PreviousState);
		break;
	case EGameState::Playing:
		OnChromaticAberrationChanged.Broadcast(bChromaticAberrationBeEnabled);
		break;
	case EGameState::InGameBookMenu:
		HUDRef->SetCurrentMenuState(EMenuState::InGameMenu, PreviousState);
		break;
	case EGameState::Pause:
		PauseGame();
		break;
	case EGameState::UnPause:
		UnPauseGame();
		break;
	case EGameState::GameOver:
		HUDRef->SetCurrentMenuState(EMenuState::GameOverScreen, PreviousState);
		break;
	default: break;
	}
	UE_LOG(LogTemp, Log, TEXT("Current Game State: %s"),
	       CurrentGameState == EGameState::Playing ? TEXT("Playing") : TEXT("Not Playing"));
}
