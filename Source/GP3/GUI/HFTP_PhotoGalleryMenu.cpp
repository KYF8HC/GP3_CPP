#include "HFTP_PhotoGalleryMenu.h"
#include "HFTP_HUD.h"
#include "HFTP_IndividualPhoto.h"
#include "Components/WrapBox.h"
#include "GP3/Systems/HFTP_GameMode.h"
#include "GP3/Systems/HFTP_Player.h"
#include "GP3/Systems/HFTP_PlayerController.h"

class UHFTP_IndividualPhoto;

void UHFTP_PhotoGalleryMenu::OnPhotoClicked(UTextureRenderTarget2D* PhotoTexture)
{
	OnIndividualPhotoClicked.Broadcast(PhotoTexture);
}

void UHFTP_PhotoGalleryMenu::RefreshPhotoGallery(bool bShouldRefresh)
{
	PhotoWrapBox->ClearChildren();
	if (AHFTP_Player* PlayerCharacter = GameModeRef->GetPlayer())
	{
		for (const auto RenderTarget : PlayerCharacter->GetPhotoRenderTargets())
		{
			if (UHFTP_IndividualPhoto* IndividualPhoto = CreateWidget<UHFTP_IndividualPhoto>(GetOwningPlayer(), IndividualPhotoClass))
			{
				IndividualPhoto->PhotoTexture = RenderTarget;
				IndividualPhoto->OnButtonClicked.AddDynamic(this, &UHFTP_PhotoGalleryMenu::OnPhotoClicked);
				PhotoWrapBox->AddChild(IndividualPhoto);
				IndividualPhoto->InitPhoto();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Character not found"));
	}
}

void UHFTP_PhotoGalleryMenu::Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex)
{
	Super::Init(InBookMenuActor, InPageSectionIndex, InPageIndex);
	if (const AHFTP_PlayerController* PlayerController = Cast<AHFTP_PlayerController>(GetOwningPlayer()))
	{
		if (AHFTP_Player* PlayerCharacter = Cast<AHFTP_Player>(PlayerController->GetCharacter()))
		{
			PlayerCharacter->OnOpenBook.AddDynamic(this, &UHFTP_PhotoGalleryMenu::RefreshPhotoGallery);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Character not found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
	}

	GameModeRef = GetWorld()->GetAuthGameMode<AHFTP_GameMode>();
	checkf(GameModeRef, TEXT("PhotoGalleryMenu::Init: GameModeRef is nullptr."));
	GameModeRef->GetHUD()->SetPhotoGalleryMenu(this);
}
