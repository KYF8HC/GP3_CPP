#include "HFTP_SketchesMenuLeftPage.h"

#include "Components/Image.h"
#include "GP3/Systems/HFTP_ObjectiveSystem.h"

void UHFTP_SketchesMenuLeftPage::Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex)
{
	SketchImage->SetVisibility(ESlateVisibility::Hidden);

	ObjectiveSystemRef = GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	ObjectiveSystemRef->OnSuccessfullyCompletedObjective.AddDynamic(this, &UHFTP_SketchesMenuLeftPage::OnObjectiveCompleted);
	ObjectiveSystemRef->OnRestartGame.AddDynamic(this, &UHFTP_SketchesMenuLeftPage::OnRestartGame);
	Super::Init(InBookMenuActor, InPageSectionIndex, InPageIndex);
}

void UHFTP_SketchesMenuLeftPage::OnObjectiveCompleted(const FHFTP_ObjectiveData& ObjectiveData)
{
	if(ObjectiveRef == ObjectiveData.ObjectiveDataAsset)
	{
		SketchImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHFTP_SketchesMenuLeftPage::OnRestartGame()
{
	SketchImage->SetVisibility(ESlateVisibility::Hidden);
}
