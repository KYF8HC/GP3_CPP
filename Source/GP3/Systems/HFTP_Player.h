#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HFTP_ObjectiveData.h"
#include "GameFramework/Character.h"
#include "HFTP_Player.generated.h"

class AHFTP_PlayerDeathAnimActor;
class UHFTP_TutorialSystem;
class USpotLightComponent;
class ABookMenuInteractionActor;
class UBookMenuInteractionComponent;
class UBookMenuComponent;
class AHFTP_PlayerController;
class UBookMenuData;
class ABookMenuActor;
class UHFTP_PhotoWidget;
class UHFTP_ObjectiveSystem;
class USphereComponent;
class UHFTP_SoundManager;
class AHFTP_GameMode;
class UCameraComponent;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCaptureScene, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenBook, bool, bOpenBook);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotoTaken, FVector, PhotoLocation);

UENUM()
enum class EHFTP_PlayerState : uint8
{
	NormalState,
	BookState,
	PhotoState
};

UENUM()
enum class ECurrentEquipped : uint8
{
	None,
	Camera,
	Compass
};

UCLASS(Abstract)
class GP3_API AHFTP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AHFTP_Player();
	void SetupBook();

	float PhotoCooldownTimer = 0.0f;

	////////////////////
	// INPUT HANDLERS //
	////////////////////

	void HandleMovement(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleLean(const FInputActionValue& Value);
	void HandleSprint(const FInputActionValue& Value);
	void HandleJump();
	void HandleEnterPhotoState();
	void HandleExitPhotoState();
	void HandleTakePhoto();
	void HandlePauseGame();
	void HandleEquipBook(int PageIndex);
	void HandleScroll(const int Value);
	bool CheckForObjective(AActor* OtherActor);
	void CheckForTutorial(AActor* OtherActor);
	void EquipItem(int ItemIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCrouch(const bool ShouldCrouch);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSprint(const bool ShouldSprint);

	UFUNCTION(BlueprintImplementableEvent)
	void OnLean(int LeanValue);

	/////////////////////////
	// OTHER MISC FUNCTIONS//
	/////////////////////////

	UFUNCTION()
	void OnObjectiveCompleted(const FHFTP_ObjectiveData& ObjectiveData);
	void ResumePlaying();
	void TakePhoto();
	void TestForPhotoObjective();

	UFUNCTION(BlueprintImplementableEvent)
	void BPResumePlaying();

	UFUNCTION(BlueprintImplementableEvent)
	void HideUI();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCompass();

	void SetupPhotoCameraMesh();
	void SetupCamera();
	void SetupInteractionSphere();

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                        const FHitResult& SweepResult);
	void MovePhotoCamera(float DeltaSeconds);
	void MoveActualCamera(float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent)
	void EquipCompass(bool bEquip, bool bShouldPlaySound = false);

	FOnCaptureScene OnCaptureScene;
	FOnOpenBook OnOpenBook;
	FOnPhotoTaken OnPhotoTaken;

	///////////////////////
	// SETTERS & GETTERS //
	///////////////////////

	void SetGameModeRef(AHFTP_GameMode* GameMode) { GameModeRef = GameMode; }
	void SetPlayerControllerRef(AHFTP_PlayerController* PlayerController) { PlayerControllerRef = PlayerController; }
	void SetTutorialSystemRef(UHFTP_TutorialSystem* TutorialSystem) { TutorialSystemRef = TutorialSystem; }
	TArray<UTextureRenderTarget2D*> GetPhotoRenderTargets() const noexcept { return PhotoRenderTargets; }

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	////////////////
	// REFERENCES //
	////////////////

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> InteractionSphere{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PhotoCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCameraRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PhotoCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneCaptureComponent2D> PlayerCameraCaptureRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextureRenderTarget2D> PhotoRenderTarget{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInstance> PhotoMaterial{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | GUI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHFTP_PhotoWidget> PhotoWidgetClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | GUI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CameraUIWidgetClass{};

	UPROPERTY()
	TObjectPtr<UUserWidget> CameraUIWidgetRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BookMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABookMenuActor> BookMenuActorRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BookMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBookMenuComponent> BookMenuComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BookMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBookMenuInteractionComponent> BookMenuInteractionComponentRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_GameMode> GameModeRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_SoundManager> SoundManagerRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_PlayerController> PlayerControllerRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_ObjectiveSystem> ObjectiveSystemRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_TutorialSystem> TutorialSystemRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PhotoCameraMesh{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Misc", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AHFTP_PlayerDeathAnimActor> DeathAnimationActor{};

	TObjectPtr<AHFTP_PlayerDeathAnimActor> DeathAnimationActorRef{};

	///////////////
	// VARIABLES //
	///////////////
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float NormalSpeed{600.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed{700.0f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Photos", meta = (AllowPrivateAccess = "true"))
	TArray<UTextureRenderTarget2D*> PhotoRenderTargets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Photos", meta = (AllowPrivateAccess = "true"))
	float PhotoCooldown{2.0f};


	bool bPhotoOnCooldown{false};


	bool bPhotoStateInitialCall{true};

	//PhotoCameraMovement
	bool bShouldMovePhotoCamera{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	FVector CameraInitialLocation{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	FVector CameraFinalLocation{};

	FVector PhotoCameraTargetLocation{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	float PhotoCameraMoveDuration{1000.0f};

	float PhotoCameraElapsedTime{};

	float ActualCameraElapsedTime{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	FVector ActualCameraInitialLocation{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	FVector ActualCameraFinalLocation{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Movement",
		meta = (AllowPrivateAccess = "true"))
	float ActualCameraMoveDuration{1000.0f};

	FVector ActualCameraTargetLocation{};

	bool bShouldMoveActualCamera{false};
	//______________________________________

	//CameraFlash
	FTimerHandle FlashTimerHandle{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PhotoCamera | Sound", meta = (AllowPrivateAccess = "true"))
	FGameplayTag CameraFlashSoundTag{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraFlash", meta = (AllowPrivateAccess = "true"))
	float OriginalExposureBias{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraFlash", meta = (AllowPrivateAccess = "true"))
	float FlashExposureBias{30.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraFlash", meta = (AllowPrivateAccess = "true"))
	float FlashDuration{0.1f};
	//___________________________________

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input",
		meta = (AllowPrivateAccess = "true", ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0"))
	float ScrollSensitivity{1.0f};

	EHFTP_PlayerState CurrentState = EHFTP_PlayerState::NormalState;

	int CurrentEquipped = 0;

	//Book related
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Book", meta = (AllowPrivateAccess = "true"))
	FVector UnEquipLocation{};
	
	bool bIsBookOpen{false};
	bool bBookOnCooldown = false;
	float BookCooldownTimer = 0.0f;
	float BookCooldownDuration = 1.5f;

	//Tutorial related
	bool bIsFirstPhoto{true};
	bool bIsSecondPhoto{true};
	bool bIsFirstBook{true};
	bool bIsFirstCompass{true};
	bool bIsFirstSprint{true};
	bool bIsFirstFireflies{true};
	bool bIsFirstLean{true};
	bool bIsFirstJump{true};
	bool bIsFirstMove{true};
	bool bIsFirstLook{true};
	
	///////////////
	// FUNCTIONS //
	///////////////

	void ResetCameraExposure();
};
