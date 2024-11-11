#include "HFTP_IndividualPhoto.h"

#include "Components/Button.h"

void UHFTP_IndividualPhoto::HandleButtonClick()
{
	OnButtonClicked.Broadcast(PhotoTexture);
}

void UHFTP_IndividualPhoto::NativeConstruct()
{
	Super::NativeConstruct();
	PhotoButton->OnClicked.Clear();
	PhotoButton->OnClicked.AddDynamic(this, &UHFTP_IndividualPhoto::HandleButtonClick);
}

UHFTP_IndividualPhoto::~UHFTP_IndividualPhoto()
{
	OnButtonClicked.Clear();
}
