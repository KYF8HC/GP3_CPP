#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "HFTP_PlayerController.generated.h"

struct FInputActionValue;
class UEnhancedInputLocalPlayerSubsystem;
class AHFTP_Player;
class UInputMappingContext;
class UInputAction;

UCLASS(Abstract)
class GP3_API AHFTP_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetInputModeToUIOnly();
	void SetInputModeToGameOnly();
	void SetInputModeToGameAndUI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Movement{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Look{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Lean{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Jump{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Sprint{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crouch{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PhotoState{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TakePhoto{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseGame{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> EquipBook{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> BookMenuScroll{};
	
	TObjectPtr<AHFTP_Player> PlayerRef{};
	TObjectPtr<UEnhancedInputComponent> InputComponentRef{};
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemRef{};

	//////////////////
	//Input related //
	//////////////////

	void SetupPlayerInputComponent();
	void HandleMovement(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleLean(const FInputActionValue& Value);
	void HandleJump();
	void HandleSprint(const FInputActionValue& Value);
	void HandleCrouch(const FInputActionValue& Value);
	void HandleTakePhoto();
	void HandleEnterPhotoState();
	void HandleExitPhotoState();
	void HandlePauseGame();
	void HandleEquipBook();
	void HandleScroll(const FInputActionValue& Value);
};
