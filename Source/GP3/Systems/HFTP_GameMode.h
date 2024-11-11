#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HFTP_GameMode.generated.h"

class UHFTP_TutorialSystem;
class UHFTP_TutorialDataAssets;
class UHFTP_SoundDataAsset;
class UHFTP_SoundManager;
class UHFTP_ObjectiveSystem;
class UHFTP_MenuBase;
class AHFTP_LevelManager;
class AHFTP_HUD;
class AHFTP_Player;
class AHFTP_PlayerController;

UENUM(BlueprintType)
enum class EGameState : uint8
{
	MainMenu,
	GameInit,
	OptionsMenu,
	TutorialMenu,
	LoadingScreen,
	CreditsMenu,
	StartPlaying,
	InGameBookMenu,
	Playing,
	Pause,
	UnPause,
	GameOver,
	None
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChromaticAberrationChanged, bool);

UCLASS(Abstract)
class GP3_API AHFTP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	
	AHFTP_GameMode();
	void QuitGame();
	void SetMainMenuState(EGameState PreviousState);

	UFUNCTION(BlueprintCallable)
	void BPChangeGameState(EGameState NewGameState, EGameState PreviousGameState = EGameState::None) { ChangeGameState(NewGameState, PreviousGameState); }
	void ChangeGameState(EGameState NewGameState, EGameState PreviousGameState = EGameState::None);

	UFUNCTION(BlueprintCallable)
	void StartGame();

	/////////////
	// GETTERS //
	/////////////
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const noexcept { return CurrentGameState; }

	UFUNCTION(BlueprintCallable)
	AHFTP_Player* GetPlayer() const noexcept { return PlayerRef; }

	UFUNCTION(BlueprintCallable)
	AHFTP_PlayerController* GetPlayerController() const noexcept { return PlayerControllerRef; }

	AHFTP_HUD* GetHUD() const noexcept { return HUDRef; }

	UHFTP_TutorialSystem* GetTutorialSystem() const noexcept { return TutorialSystemRef; }

	const TArray<TObjectPtr<UHFTP_TutorialDataAssets>>& GetTutorialDataAssets() const noexcept { return TutorialDataAssets; }
	
	///////////////
	// VARIABLES //
	///////////////
	
	//TODO: This is a temporary solution to get the level name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	TArray<FName> GameLevelNames{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UHFTP_TutorialDataAssets>> TutorialDataAssets{};

	//Accessibility
	UPROPERTY(BlueprintReadWrite, Category = "Accessibility")
	bool bShouldFlashlightBeEnabled{true};

	UPROPERTY(BlueprintReadWrite, Category = "Accessibility")
	bool bChromaticAberrationBeEnabled{true};
	
	UFUNCTION(BlueprintCallable)
	void SetChromaticAberration(bool bShouldEnable) noexcept;

	FOnChromaticAberrationChanged OnChromaticAberrationChanged{};
	
protected:
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;

private:
	//////////////////////
	// CLASS REFERENCES //
	//////////////////////
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHFTP_LevelManager> LevelManagerClassRef{};
	
	///////////////////////
	// OBJECT REFERENCES //
	///////////////////////
	TObjectPtr<AHFTP_Player> PlayerRef{};
	TObjectPtr<AHFTP_PlayerController> PlayerControllerRef{};
	TObjectPtr<AHFTP_HUD> HUDRef{};
	TObjectPtr<UHFTP_SoundManager> SoundManagerRef{};
	TObjectPtr<AHFTP_LevelManager> LevelManagerRef{};
	TObjectPtr<UHFTP_TutorialSystem> TutorialSystemRef{};
	TObjectPtr<UHFTP_ObjectiveSystem> ObjectiveSystemRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_SoundDataAsset> SoundDataAsset{};
	
	EGameState CurrentGameState = EGameState::GameInit;

	FVector PlayerStartLocation{};

	///////////////
	// FUNCTIONS //
	///////////////
	void CreateSystems();
	void SetupPlayer();
	void SaveReferences();
	void InjectReferences();
	void PauseGame();
	void UnPauseGame();
	void UnLoadAllLevels();
	void GameOver();

};
