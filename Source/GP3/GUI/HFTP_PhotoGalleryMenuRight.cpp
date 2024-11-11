#include "HFTP_PhotoGalleryMenuRight.h"
#include "HFTP_HUD.h"
#include "HFTP_PhotoGalleryMenu.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "GP3/Systems/HFTP_GameMode.h"

void UHFTP_PhotoGalleryMenuRight::SetBigPhotoTexture(UTextureRenderTarget2D* PhotoTexture)
{
	BigPhotoTexture = PhotoTexture;
	InitBigPhoto();
	if (Border->GetVisibility() == ESlateVisibility::Hidden)
		Border->SetVisibility(ESlateVisibility::Visible);
}

void UHFTP_PhotoGalleryMenuRight::Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex)
{
	GameModeRef = GetWorld()->GetAuthGameMode<AHFTP_GameMode>();
	checkf(GameModeRef, TEXT("PhotoGalleryMenuRight::Init: GameModeRef is nullptr."));
	GameModeRef->GetHUD()->SetPhotoGalleryMenuRight(this);

	PhotoGalleryMenuRef = GameModeRef->GetHUD()->GetPhotoGalleryMenu();
	PhotoGalleryMenuRef->OnIndividualPhotoClicked.AddDynamic(this, &UHFTP_PhotoGalleryMenuRight::SetBigPhotoTexture);

	Super::Init(InBookMenuActor, InPageSectionIndex, InPageIndex);
}
