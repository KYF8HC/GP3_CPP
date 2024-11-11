#include "HFTP_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HFTP_Player.h"

void AHFTP_PlayerController::SetInputModeToUIOnly()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AHFTP_PlayerController::SetInputModeToGameOnly()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AHFTP_PlayerController::SetInputModeToGameAndUI()
{
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}


void AHFTP_PlayerController::OnPossess(APawn* InPawn)
{
	PlayerRef = Cast<AHFTP_Player>(InPawn);
	checkf(PlayerRef, TEXT("AHFTP_PlayerController::OnPossess: Player is not valid"));

	InputComponentRef = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(InputComponentRef, TEXT("AHFTP_PlayerController::OnPossess: inputComponent is not valid"));

	InputSubsystemRef = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystemRef, TEXT("AHFTP_Player::BeginPlay: InputComponent is nullptr"));
	InputSubsystemRef->AddMappingContext(MappingContext, 0);

	SetupPlayerInputComponent();
	
	Super::OnPossess(InPawn);
}

void AHFTP_PlayerController::SetupPlayerInputComponent()
{
	checkf(InputComponentRef, TEXT("AHFTP_PlayerController::SetInputs: InputComponent is nullptr"));
	
	InputComponentRef->BindAction(Movement, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleMovement);
	InputComponentRef->BindAction(Look, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleLook);
	InputComponentRef->BindAction(Jump, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleJump);
	InputComponentRef->BindAction(Sprint, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleSprint);
	InputComponentRef->BindAction(Crouch, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleCrouch);
	InputComponentRef->BindAction(TakePhoto, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleTakePhoto);
	InputComponentRef->BindAction(PhotoState, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleEnterPhotoState);
	InputComponentRef->BindAction(PhotoState, ETriggerEvent::Completed, this, &AHFTP_PlayerController::HandleExitPhotoState);
	InputComponentRef->BindAction(PauseGame, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandlePauseGame);
	InputComponentRef->BindAction(EquipBook, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleEquipBook);
	InputComponentRef->BindAction(BookMenuScroll, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleScroll);
	InputComponentRef->BindAction(Lean, ETriggerEvent::Triggered, this, &AHFTP_PlayerController::HandleLean);
	InputComponentRef->BindAction(Lean, ETriggerEvent::Completed, this, &AHFTP_PlayerController::HandleLean);
}

void AHFTP_PlayerController::HandleMovement(const FInputActionValue& Value)
{
	PlayerRef->HandleMovement(Value);
}

void AHFTP_PlayerController::HandleLook(const FInputActionValue& Value)
{
	PlayerRef->HandleLook(Value);
}

void AHFTP_PlayerController::HandleLean(const FInputActionValue& Value)
{
	PlayerRef->HandleLean(Value);
}

void AHFTP_PlayerController::HandleJump()
{
	PlayerRef->HandleJump(); 
}

void AHFTP_PlayerController::HandleSprint(const FInputActionValue& Value)
{
	PlayerRef->HandleSprint(Value);
}

void AHFTP_PlayerController::HandleCrouch(const FInputActionValue& Value)
{
	PlayerRef->OnCrouch(Value.Get<bool>());
}

void AHFTP_PlayerController::HandleTakePhoto()
{
	PlayerRef->HandleTakePhoto();
}

void AHFTP_PlayerController::HandleEnterPhotoState()
{
	
	PlayerRef->HandleEnterPhotoState();
}

void AHFTP_PlayerController::HandleExitPhotoState()
{
	PlayerRef->HandleExitPhotoState();
}

void AHFTP_PlayerController::HandlePauseGame()
{
	PlayerRef->HandlePauseGame();
}

void AHFTP_PlayerController::HandleEquipBook()
{
	PlayerRef->HandleEquipBook(0);
}

void AHFTP_PlayerController::HandleScroll(const FInputActionValue& Value)
{
	PlayerRef->HandleScroll(Value.Get<float>());
}

