#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GP3/Systems/HFTP_LevelManager.h"
#include "GP3/Systems/HFTP_ObjectiveSystem.h"
#include "HFTP_HUD.generated.h"

class AHFTP_LevelManager;
class UHFTP_GameOverScreen;
class UHFTP_LoadingScreen;
class UHFTP_TutorialPromptHUD;
class UHFTP_PhotoGalleryMenuRight;
class UHFTP_PhotoGalleryMenu;
class UHFTP_TutorialMenu;
class UHFTP_ActiveObjectivesMenu;
enum class EGameState : uint8;
class AHFTP_GameMode;
class UHFTP_SoundManager;
class UHFTP_ObjectiveSystem;
class UHFTP_MenuBase;
class UHFTP_CreditsMenu;
class UHFTP_PauseMenu;
class UHFTP_OptionsMenu;
class UHFTP_MainMenu;

UENUM(BlueprintType)
enum class EMenuState
{
	HUDInit,
	Main,
	Options,
	Pause,
	TutorialMenu,
	LoadingScreen,
	InGame,
	InGameMenu,
	Credits,
	GameOverScreen,
	NoneMenu
};

UCLASS(Abstract)
class AHFTP_HUD : public AHUD
{
	GENERATED_BODY()

public:
	void Initialize();


	//////////////////////
	// SETTERS & GETTERS//
	//////////////////////
	
	void SetCurrentMenuState(EMenuState NewMenuState, EGameState PreviousState);
	void SetSystemReferences(AHFTP_GameMode& GameMode, AHFTP_LevelManager* LevelManager) noexcept;
	void SetPhotoGalleryMenuRight(UHFTP_PhotoGalleryMenuRight* PhotoGalleryMenuRight) noexcept { PhotoGalleryMenuRightRef = PhotoGalleryMenuRight; }
	void SetPhotoGalleryMenu(UHFTP_PhotoGalleryMenu* PhotoGalleryMenu) noexcept { PhotoGalleryMenuRef = PhotoGalleryMenu; }

	UHFTP_PhotoGalleryMenu* GetPhotoGalleryMenu() const noexcept { return  PhotoGalleryMenuRef; }
private:
	void CreateMenus();
	void InitializeMenus();

	FString GetMenuStateAsString(EMenuState MenuState) const noexcept;
	FString GetGameStateAsString(EGameState GameState) const noexcept;

	////////////////////////////////
	// MENU REFERENCES & POINTERS //
	////////////////////////////////
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_MainMenu> MainMenuWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_OptionsMenu> OptionsMenuWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_PauseMenu> PauseMenuWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_CreditsMenu> CreditsMenuWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_TutorialMenu> TutorialMenuClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_TutorialPromptHUD> TutorialPromptHUDClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_LoadingScreen> LoadingScreenClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_GameOverScreen> GameOverScreenWidgetClass{};

	UPROPERTY(VisibleAnywhere, Category= "Debug", meta = (AllowPrivateAccess = "true"))
	EMenuState CurrentMenuState = EMenuState::HUDInit;

	TObjectPtr<AHFTP_GameMode> GameModeRef{};
	TObjectPtr<UHFTP_SoundManager> SoundManagerRef{};
	TObjectPtr<AHFTP_LevelManager> LevelManagerRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_MainMenu> MainMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_OptionsMenu> OptionsMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_PauseMenu> PauseMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_CreditsMenu> CreditsMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_TutorialMenu> TutorialMenuRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_PhotoGalleryMenu> PhotoGalleryMenuRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_PhotoGalleryMenuRight> PhotoGalleryMenuRightRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_TutorialPromptHUD> TutorialPromptHUDRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_LoadingScreen> LoadingScreenRef{};

	UPROPERTY()
	TObjectPtr<UHFTP_GameOverScreen> GameOverScreenWidgetRef{};
	
	TObjectPtr<UHFTP_MenuBase> CurrentMenu{};
};
