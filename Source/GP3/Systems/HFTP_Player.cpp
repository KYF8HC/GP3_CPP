#include "HFTP_Player.h"

#include "HFTP_GameMode.h"
#include "HFTP_ObjectiveInteractable.h"
#include "HFTP_ObjectiveSystem.h"
#include "HFTP_PlayerController.h"
#include "HFTP_PlayerDeathAnimActor.h"
#include "HFTP_SoundManager.h"
#include "HFTP_TutorialComponent.h"
#include "HFTP_TutorialSystem.h"
#include "InputActionValue.h"
#include "Actors/BookMenuActor.h"
#include "Actors/BookMenuInteractionActor.h"
#include "Blueprint/UserWidget.h"
#include "GP3/GUI/HFTP_PhotoWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BookMenuComponent.h"
#include "Components/BookMenuInteractionComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GP3/AI/FinalBoss.h"
#include "GP3/DataAssets/HFTP_TutorialDataAssets.h"
#include "Kismet/KismetSystemLibrary.h"


void AHFTP_Player::SetupPhotoCameraMesh()
{
	PhotoCameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhotoCameraMesh"));
	PhotoCameraMesh->SetupAttachment(RootComponent);
}

void AHFTP_Player::SetupCamera()
{
	PlayerCameraRef = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraRef->SetupAttachment(RootComponent);
	PlayerCameraRef->bUsePawnControlRotation = true;
	PlayerCameraRef->PostProcessSettings.bOverride_ColorGamma = true;

	PlayerCameraCaptureRef = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PlayerCameraCapture"));
	PlayerCameraCaptureRef->SetupAttachment(PlayerCameraRef);
	PlayerCameraCaptureRef->TextureTarget = PhotoRenderTarget;
	PlayerCameraCaptureRef->bAlwaysPersistRenderingState = true;
	PlayerCameraCaptureRef->bCaptureEveryFrame = false;
	PlayerCameraCaptureRef->bCaptureOnMovement = false;
	PlayerCameraCaptureRef->PostProcessSettings.bOverride_ColorGamma = true;
}

void AHFTP_Player::SetupInteractionSphere()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHFTP_Player::HandleBeginOverlap);
}

AHFTP_Player::AHFTP_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupCamera();
	SetupInteractionSphere();
	SetupBook();
	SetupPhotoCameraMesh();
}

void AHFTP_Player::SetupBook()
{
	BookMenuComponentRef = CreateDefaultSubobject<UBookMenuComponent>(TEXT("BookMenuComponent"));
	BookMenuInteractionComponentRef = CreateDefaultSubobject<UBookMenuInteractionComponent>(
		TEXT("BookMenuInteractionComponent"));

	BookMenuComponentRef->SetupAttachment(PlayerCameraRef);
	BookMenuInteractionComponentRef->SetupAttachment(PlayerCameraRef);
}

void AHFTP_Player::OnObjectiveCompleted(const FHFTP_ObjectiveData& ObjectiveData)
{
	HandleExitPhotoState();
	HandleEquipBook(ObjectiveData.ObjectiveDataAsset->PageIndex);
}

void AHFTP_Player::ResumePlaying()
{
	PhotoRenderTargets.Empty();
	ObjectiveSystemRef = GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	ObjectiveSystemRef->OnUpdateObjectiveList.AddUObject(this, &AHFTP_Player::UpdateCompass);
	ObjectiveSystemRef->OnSuccessfullyCompletedObjective.AddDynamic(this, &AHFTP_Player::OnObjectiveCompleted);
	GetCharacterMovement()->GravityScale = 2.0f;
	BPResumePlaying();

	if (BookMenuComponentRef->BookMenuActor)
	{
		BookMenuActorRef = BookMenuComponentRef->BookMenuActor;
		BookMenuActorRef->CloseBook();
		BookMenuActorRef->RegisterInteractionComponent(BookMenuInteractionComponentRef);
		BookMenuInteractionComponentRef->InteractionActor->SetActorHiddenInGame(true);
	}
	PlayerCameraRef->PostProcessSettings.AutoExposureBias = OriginalExposureBias;
	CameraUIWidgetRef = CreateWidget<UUserWidget>(GetWorld(), CameraUIWidgetClass);
	HandleLean(0);
}


void AHFTP_Player::HandleMovement(const FInputActionValue& Value)
{
	if (CurrentState == EHFTP_PlayerState::BookState)
		return;
	const FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);

	if (!TutorialSystemRef->bIsTutorialActive(ETutorialType::Move))
		return;

	if (bIsFirstMove)
	{
		bIsFirstMove = false;
		if (!bIsFirstJump && !bIsFirstLook)
		{
			UE_LOG(LogTemp, Log, TEXT("AHFTP_Player::HandleMove: Completing tutorial"));
			TutorialSystemRef->CompleteTutorial(ETutorialType::Move);
		}
	}
}

void AHFTP_Player::HandleLook(const FInputActionValue& Value)
{
	if (CurrentState == EHFTP_PlayerState::BookState)
		return;
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);

	if (!TutorialSystemRef->bIsTutorialActive(ETutorialType::Move))
		return;

	if (bIsFirstLook)
	{
		bIsFirstLook = false;
		if (!bIsFirstJump && !bIsFirstMove)
		{
			UE_LOG(LogTemp, Log, TEXT("AHFTP_Player::HandleLook: Completing tutorial"));
			TutorialSystemRef->CompleteTutorial(ETutorialType::Move);
		}
	}
}

void AHFTP_Player::HandleLean(const FInputActionValue& Value)
{
	int LeanValue = Value.Get<float>() + 1;
	OnLean(LeanValue);

	if (TutorialSystemRef->bIsTutorialActive(ETutorialType::Lean))
	{
		bIsFirstLean = false;
		TutorialSystemRef->CompleteTutorial(ETutorialType::Lean);
	}
}

void AHFTP_Player::HandleJump()
{
	if (CurrentState == EHFTP_PlayerState::BookState)
		return;
	Jump();

	if (!TutorialSystemRef->bIsTutorialActive(ETutorialType::Move))
		return;

	if (bIsFirstJump)
	{
		bIsFirstJump = false;
		if (!bIsFirstLook && !bIsFirstMove)
		{
			UE_LOG(LogTemp, Log, TEXT("AHFTP_Player::HandleJump: Completing tutorial"));
			TutorialSystemRef->CompleteTutorial(ETutorialType::Move);
		}
	}
}

void AHFTP_Player::HandleEnterPhotoState()
{
	if (static_cast<ECurrentEquipped>(CurrentEquipped) != ECurrentEquipped::Camera)
		return;

	if (CurrentState == EHFTP_PlayerState::BookState)
		return;

	if (bPhotoStateInitialCall)
	{
		PhotoCameraTargetLocation = CameraFinalLocation;
		ActualCameraTargetLocation = ActualCameraFinalLocation;
		bShouldMovePhotoCamera = true;
		bShouldMoveActualCamera = false;
		PhotoCameraElapsedTime = 0.0f;
		bPhotoStateInitialCall = false;
	}
}

void AHFTP_Player::HandleExitPhotoState()
{
	if (static_cast<ECurrentEquipped>(CurrentEquipped) != ECurrentEquipped::Camera)
		return;

	if (CurrentState == EHFTP_PlayerState::BookState)
		return;

	if (CameraUIWidgetRef)
		CameraUIWidgetRef->RemoveFromParent();
	CurrentState = EHFTP_PlayerState::NormalState;
	PhotoCameraTargetLocation = CameraInitialLocation;
	ActualCameraTargetLocation = ActualCameraInitialLocation;
	bShouldMoveActualCamera = true;
	bShouldMovePhotoCamera = false;
	ActualCameraElapsedTime = 0.0f;
	PhotoCameraElapsedTime = 0.0f;
	bPhotoStateInitialCall = true;
}

void AHFTP_Player::TakePhoto()
{
	//if (PlayerCameraCaptureRef->TextureTarget)
	//{
	//	PlayerCameraCaptureRef->TextureTarget->ConditionalBeginDestroy();
	//	PlayerCameraCaptureRef->TextureTarget = nullptr;
	//}
	PlayerCameraCaptureRef->TextureTarget = NewObject<UTextureRenderTarget2D>();
	PlayerCameraCaptureRef->TextureTarget->InitAutoFormat(1920, 1080);
	PlayerCameraCaptureRef->TextureTarget->RenderTargetFormat = RTF_RGBA16f;


	OnCaptureScene.Broadcast(true);

	if (PlayerCameraRef)
	{
		// Change exposure settings to simulate flash
		PlayerCameraRef->PostProcessSettings.ColorGamma = FVector4(2.0f, 2.0f, 2.0f, 1.0f);
		PlayerCameraCaptureRef->PostProcessSettings.ColorGamma = FVector4(2.0f, 2.0f, 2.0f, 1.0f);

		// Set a timer to reset the exposure back to normal after a short duration
		GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &AHFTP_Player::ResetCameraExposure,
		                                       FlashDuration, false);
	}

	PlayerCameraCaptureRef->CaptureScene();
	OnPhotoTaken.Broadcast(GetActorLocation());
	GetGameInstance()->GetSubsystem<UHFTP_SoundManager>()->PlaySound(CameraFlashSoundTag, this, false);
	if (PhotoWidgetClass)
	{
		auto widget = CreateWidget<UHFTP_PhotoWidget>(GetWorld(), PhotoWidgetClass);
		widget->PhotoTexture = PlayerCameraCaptureRef->TextureTarget;
		widget->AddToViewport();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AHFTP_Player::HandleTakePhoto: PhotoWidgetClass is nullptr"));


	PhotoRenderTargets.Add(PlayerCameraCaptureRef->TextureTarget);
	OnCaptureScene.Broadcast(false);

	if (TutorialSystemRef->bIsTutorialActive(ETutorialType::PhotoFirst))
	{
		bIsFirstPhoto = false;
		TutorialSystemRef->CompleteTutorial(ETutorialType::PhotoFirst);
	}

	if (TutorialSystemRef->bIsTutorialActive(ETutorialType::PhotoSecond))
	{
		bIsSecondPhoto = false;
		TutorialSystemRef->CompleteTutorial(ETutorialType::PhotoSecond);
	}
}

void AHFTP_Player::TestForPhotoObjective()
{
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), PlayerCameraRef->GetComponentLocation(),
	                                        PlayerCameraRef->GetComponentLocation() + PlayerCameraRef->
	                                        GetForwardVector() * 1000.0f, 50.0f,
	                                        TraceTypeQuery1,
	                                        false,
	                                        TArray<AActor*>
	                                        {
		                                        this,
	                                        	BookMenuActorRef,
	                                        	BookMenuInteractionComponentRef->InteractionActor
	                                        },
	                                        EDrawDebugTrace::None, HitResult,
	                                        true);
	if (HitResult.GetActor())
		UE_LOG(LogTemp, Log, TEXT("AHFTP_Player::TestForPhotoObjective: HitResult: %s"), *HitResult.GetActor()->GetName());
	if (HitResult.bBlockingHit)
	{
		TObjectPtr<UHFTP_ObjectiveInteractable> Interactable =
			Cast<UHFTP_ObjectiveInteractable>(
				HitResult.GetActor()->GetComponentByClass(UHFTP_ObjectiveInteractable::StaticClass()));
		if (Interactable)
		{
			if (!Interactable->GetObjectiveData().IsValid())
			{
				return;
			}
			auto ObjectiveType = Interactable->GetObjectiveData().ObjectiveDataAsset->GetObjectiveType();
			if (ObjectiveType == EObjectiveType::Photo)
			{
				Interactable->CompleteObjective();
			}
		}
	}
}

void AHFTP_Player::HandleTakePhoto()
{
	if (CurrentState == EHFTP_PlayerState::BookState)
	{
		BookMenuInteractionComponentRef->GetWidgetInteractionComponent()->PressPointerKey(EKeys::LeftMouseButton);
		BookMenuInteractionComponentRef->GetWidgetInteractionComponent()->ReleasePointerKey(EKeys::LeftMouseButton);
		return;
	}
	if (CurrentState != EHFTP_PlayerState::PhotoState || bPhotoOnCooldown)
		return;

	TakePhoto();
	TestForPhotoObjective();
	bPhotoOnCooldown = true;
}

void AHFTP_Player::HandlePauseGame()
{
	if (CurrentState == EHFTP_PlayerState::BookState)
		return;
	GameModeRef->ChangeGameState(EGameState::Pause);
}

void AHFTP_Player::HandleEquipBook(int PageIndex)
{
	if (bBookOnCooldown)
		return;

	if (!bIsBookOpen)
	{
		bBookOnCooldown = true;
		//Hide the camera and compass
		CurrentEquipped = 0;
		PhotoCameraMesh->SetVisibility(false);

		if (CurrentEquipped == 2)EquipCompass(false, true);
		else EquipCompass(false);

		CameraUIWidgetRef->RemoveFromParent();

		//Open the book
		BookMenuActorRef->OpenBookAt(PageIndex);
		CurrentState = EHFTP_PlayerState::BookState;
		PlayerControllerRef->SetInputModeToGameAndUI();
		OnOpenBook.Broadcast(false);
		bIsBookOpen = true;

		return;
	}

	// Close the book
	bBookOnCooldown = true;
	BookMenuActorRef->CloseBook();
	CurrentState = EHFTP_PlayerState::NormalState;
	PlayerControllerRef->SetInputModeToGameOnly();
	OnOpenBook.Broadcast(true);
	bIsBookOpen = false;

	if (TutorialSystemRef->bIsTutorialActive(ETutorialType::Book))
	{
		bIsFirstBook = false;
		TutorialSystemRef->CompleteTutorial(ETutorialType::Book);
	}
}

void AHFTP_Player::EquipItem(int ItemIndex)
{
	if (ItemIndex < 0)
		ItemIndex = 2;
	else if (ItemIndex > 2)
		ItemIndex = 0;

	switch (ItemIndex)
	{
	case 0:
		PhotoCameraMesh->SetVisibility(false);
		if (CurrentEquipped == 2)EquipCompass(false, true);
		else EquipCompass(false);
		break;
	case 1:
		PhotoCameraMesh->SetVisibility(true);
		if (CurrentEquipped == 2)EquipCompass(false, true);
		else EquipCompass(false);
		break;
	case 2:
		PhotoCameraMesh->SetVisibility(false);
		EquipCompass(true, true);
		break;
	default: break;
	}

	CurrentEquipped = ItemIndex;
}

void AHFTP_Player::HandleScroll(const int Value)
{
	if (CurrentState == EHFTP_PlayerState::BookState)
	{
		BookMenuInteractionComponentRef->GetWidgetInteractionComponent()->ScrollWheel(Value * ScrollSensitivity);
		return;
	}

	if (CurrentState != EHFTP_PlayerState::NormalState)
		return;

	EquipItem(CurrentEquipped + Value);
}

bool AHFTP_Player::CheckForObjective(AActor* OtherActor)
{
	//Check if the overlapped actor is an ObjectiveInteractable

	if (auto Interactable = OtherActor->FindComponentByClass<UHFTP_ObjectiveInteractable>())
	{
		if (!Interactable->GetObjectiveData().IsValid())
			return true;
		auto ObjectiveType = Interactable->GetObjectiveData().ObjectiveDataAsset->GetObjectiveType();
		if (ObjectiveType == EObjectiveType::Explore)
		{
			Interactable->CompleteObjective();
		}
	}
	return false;
}

void AHFTP_Player::CheckForTutorial(AActor* OtherActor)
{
	if (auto Tutorial = OtherActor->FindComponentByClass<UHFTP_TutorialComponent>())
	{
		if (Tutorial->TutorialType == ETutorialType::Fireflies)
			TutorialSystemRef->CompleteTutorial(ETutorialType::Fireflies);
		else if (Tutorial->TutorialType == ETutorialType::Compass)
			TutorialSystemRef->CompleteTutorial(ETutorialType::Compass);
	}
}

void AHFTP_Player::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (Cast<AFinalBoss>(OtherActor))
	{
		ObjectiveSystemRef->OnUpdateObjectiveList.RemoveAll(this);
		ObjectiveSystemRef->OnSuccessfullyCompletedObjective.RemoveDynamic(this, &AHFTP_Player::OnObjectiveCompleted);
		//PlayDeathAnimation
		DeathAnimationActorRef = GetWorld()->SpawnActor<AHFTP_PlayerDeathAnimActor>(DeathAnimationActor);
		DeathAnimationActorRef->SetActorLocation(GetActorLocation());
		DeathAnimationActorRef->SetGameModeRef(GameModeRef);
		DeathAnimationActorRef->PlayDeathAnimation();

		OtherActor->Destroy();
		return;
	}

	if (CheckForObjective(OtherActor)) return;
	CheckForTutorial(OtherActor);
}

void AHFTP_Player::MovePhotoCamera(float DeltaSeconds)
{
	if (bShouldMovePhotoCamera)
	{
		PhotoCameraElapsedTime += DeltaSeconds;
		FVector NewLocation = FMath::Lerp(PhotoCameraMesh->GetRelativeLocation(), PhotoCameraTargetLocation,
		                                  PhotoCameraElapsedTime / PhotoCameraMoveDuration);
		if (PhotoCameraElapsedTime > PhotoCameraMoveDuration)
		{
			NewLocation = PhotoCameraTargetLocation;
			bShouldMovePhotoCamera = false;
			PhotoCameraElapsedTime = 0.0f;
		}
		PhotoCameraMesh->SetRelativeLocation(NewLocation);
		if (PhotoCameraMesh->GetRelativeLocation().Equals(CameraFinalLocation, 0.2f))
		{
			ActualCameraElapsedTime = 0.0f;
			bShouldMoveActualCamera = true;
		}
	}
}

void AHFTP_Player::MoveActualCamera(float DeltaSeconds)
{
	if (bShouldMoveActualCamera)
	{
		ActualCameraElapsedTime += DeltaSeconds;
		FVector NewLocation = FMath::Lerp(PlayerCameraRef->GetRelativeLocation(), ActualCameraTargetLocation,
		                                  ActualCameraElapsedTime / ActualCameraMoveDuration);
		if (ActualCameraElapsedTime > ActualCameraMoveDuration)
		{
			NewLocation = ActualCameraTargetLocation;
			bShouldMoveActualCamera = false;
			ActualCameraElapsedTime = 0.0f;
		}
		PlayerCameraRef->SetRelativeLocation(NewLocation);

		if (PlayerCameraRef->GetRelativeLocation().Equals(ActualCameraFinalLocation, 0.1f))
		{
			CurrentState = EHFTP_PlayerState::PhotoState;
			CameraUIWidgetRef->AddToViewport();
		}
		if (PlayerCameraRef->GetRelativeLocation().Equals(ActualCameraInitialLocation, 0.1f))
		{
			PhotoCameraElapsedTime = 0.0f;
			bShouldMovePhotoCamera = true;
		}
	}
}

void AHFTP_Player::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bPhotoOnCooldown)
	{
		PhotoCooldownTimer += DeltaSeconds;
		if (PhotoCooldownTimer >= PhotoCooldown)
		{
			bPhotoOnCooldown = false;
			PhotoCooldownTimer = 0.0f;
		}
	}

	if (bBookOnCooldown)
	{
		BookCooldownTimer += DeltaSeconds;
		if (BookCooldownTimer >= BookCooldownDuration)
		{
			bBookOnCooldown = false;
			BookCooldownTimer = 0.0f;
		}
	}

	MovePhotoCamera(DeltaSeconds);
	MoveActualCamera(DeltaSeconds);
	if (CurrentState == EHFTP_PlayerState::PhotoState)
		PlayerCameraRef->SetRelativeLocation(ActualCameraFinalLocation);
}

void AHFTP_Player::ResetCameraExposure()
{
	PlayerCameraRef->PostProcessSettings.ColorGamma = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	PlayerCameraCaptureRef->PostProcessSettings.ColorGamma = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
}

void AHFTP_Player::HandleSprint(const FInputActionValue& Value)
{
	if (CurrentState == EHFTP_PlayerState::BookState)
		return;
	const bool bValue = Value.Get<bool>();
	OnSprint(bValue);

	if (TutorialSystemRef->bIsTutorialActive(ETutorialType::Sprint))
	{
		bIsFirstSprint = false;
		TutorialSystemRef->CompleteTutorial(ETutorialType::Sprint);
	}
}
